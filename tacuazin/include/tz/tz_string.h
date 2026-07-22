#pragma once

#include <stddef.h>

typedef struct {
    char *buffer;
    size_t length;
} TzString;

TzString tz_string_from_cstring(char *cstring);
