#pragma once

#include "tz/tz_string.h"
#include "tz/tz_vector.h"
#include "tz_allocator.h"

typedef struct TzWindow TzWindow;

TzWindow *tz_window_make(TzString title, TzVector2i dimentions, TzAllocator allocator);
void tz_window_destroy(TzWindow *window, TzAllocator allocator);
void tz_window_poll_events(TzWindow *window);
int tz_window_should_close(TzWindow *window);
