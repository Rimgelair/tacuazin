#include "tz/tz_window.h"

#include <Windows.h>
#include <stdlib.h>
#include <stringapiset.h>

struct TzWindow {
  HINSTANCE h_instance;
  HWND window_handle;
  int width;
  int height;
  int should_close;
};

wchar_t* tz_string_to_wide(const TzString *str);

static LRESULT CALLBACK tz_win32_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
  TzWindow *window = (TzWindow *)GetWindowLongPtrW(hwnd, GWLP_USERDATA);

  switch(uMsg){
    case WM_NCCREATE: {
      CREATESTRUCT *cs = (CREATESTRUCT *)lParam;
      SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)cs->lpCreateParams);
      return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }
    case WM_DESTROY:
      if(window) window->should_close = 1;
      return 0;
  }

  return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

TzWindow *tz_window_make(TzString title, TzVector2i dimensions){
  TzWindow *newwindow = malloc(sizeof(TzWindow));
  newwindow->h_instance = GetModuleHandle(NULL);

  newwindow->width = dimensions.x;
  newwindow->height = dimensions.y;

  wchar_t *titleW = tz_string_to_wide(&title);

  const wchar_t className[] = L"TacuazinWindowClass";

  WNDCLASSW windowClass = {
    .lpfnWndProc = tz_win32_proc,
    .hInstance = newwindow->h_instance,
    .lpszClassName = className,
  };

  RegisterClassW(&windowClass);

  newwindow->window_handle = CreateWindowExW(0,
                                            className,
                                            titleW,
                                            WS_OVERLAPPEDWINDOW,
                                            CW_USEDEFAULT, CW_USEDEFAULT,
                                            newwindow->width, newwindow->height,
                                            NULL, NULL, newwindow->h_instance, newwindow);

  ShowWindow(newwindow->window_handle, SW_SHOWNORMAL);
  newwindow->should_close = 0;

  // TODO: maybe use temp allocator here
  free(titleW);

  return newwindow;
}

void tz_window_poll_events(TzWindow *window)
{
  MSG msg = {0};
  while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

int tz_window_should_close(TzWindow *window){
  return window->should_close;
}

void tz_window_destroy(TzWindow *window){
  DestroyWindow(window->window_handle);
  UnregisterClassW(L"TacuazinWindowClass", window->h_instance);
  free(window);
}

wchar_t* tz_string_to_wide(const TzString *str){
  if(!str || !str->buffer) return NULL;

  int wideLen = MultiByteToWideChar(CP_UTF8, 0, str->buffer, (int)str->length, NULL, 0);
  if (wideLen == 0) return NULL;

  wchar_t *wbuffer = (wchar_t*)malloc((wideLen + 1) * sizeof(wchar_t));
  if(!wbuffer) return NULL;

  MultiByteToWideChar(CP_UTF8, 0, str->buffer, (int)str->length, wbuffer, wideLen);
  wbuffer[wideLen] = L'\0';

  return wbuffer;
}
