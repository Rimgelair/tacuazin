#pragma once

#include "tz/tz_vector.h"
#include "tz/tz_string.h"

typedef struct TzApp TzApp;

typedef struct {
  TzString title;
  TzVector2i dimensions;
} TzAppProps;

TzApp * tz_app_make(TzAppProps *appProps);
void tz_app_run(TzApp *app);
void tz_app_destroy(TzApp *app);
