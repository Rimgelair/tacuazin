#pragma once

#include "tz/tz_assert.h"

#include <stdbool.h>
#include <stdint.h>

#define kib(bytes) ((size_t)(bytes) * 1024ULL)
#define mib(bytes) (kib(bytes) * 1024ULL)
#define gib(bytes) (mib(bytes) * 1024ULL)

static inline bool is_power_of_two(uintptr_t value) {
    return value && ((value & (value - 1)) == 0);
}

static inline uintptr_t align_forward(uintptr_t address, size_t alignment) {

    TZ_ASSERT(is_power_of_two(alignment));

    return (address + (alignment - 1)) & ~(alignment - 1);
}

size_t get_platform_page_size();
