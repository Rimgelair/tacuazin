#pragma once

#include "tz/tz_string.h"

typedef struct TzApp TzApp;

TzApp * tz_app_make(TzString title, int width, int height);
void tz_app_destroy(TzApp *app);
