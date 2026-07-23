#include "tz/tz_app.h"
#include "tz/tz_allocator.h"
#include "tz/tz_memory.h"
#include "tz/tz_stack_allocator.h"
#include "tz/tz_window.h"

#include <stdlib.h>

struct TzApp {
    TzAppProps app_props;
    TzStackAllocator temp_allocator;
    TzWindow *window;
};

TzApp *tz_app_make(TzAppProps *appProps) {

    // Allocator Setup
    void *arenaBackingBuffer = malloc(mib(1));
    TzStackAllocator arena;
    tz_stack_allocator_init(&arena, arenaBackingBuffer, mib(1));
    TzAllocator temp = tz_stack_allocator_as_allocator(&arena);

    TzApp *newApp = tz_allocator_alloc(temp, TzApp);
    newApp->app_props = *appProps;
    newApp->window = tz_window_make(newApp->app_props.title, newApp->app_props.dimensions, temp);
    newApp->temp_allocator = arena;

    return newApp;
}

void tz_app_run(TzApp *app) {
    while (!tz_window_should_close(app->window)) {
        tz_window_poll_events(app->window);
    }
}

void tz_app_destroy(TzApp *app) {
    tz_window_destroy(app->window, tz_stack_allocator_as_allocator(&app->temp_allocator));
    free(app->temp_allocator.buffer);
}
