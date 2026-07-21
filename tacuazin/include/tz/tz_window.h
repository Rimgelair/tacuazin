#pragma once

#include "tz/tz_string.h"
#include "tz/tz_vector.h"

typedef struct TzWindow TzWindow;

TzWindow *tz_window_make(TzString title, TzVector2i dimentions);
void tz_window_destroy(TzWindow *window);
void tz_window_poll_events(TzWindow *window);
int tz_window_should_close(TzWindow *window);
