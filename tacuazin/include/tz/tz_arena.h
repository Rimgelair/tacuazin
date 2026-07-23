#pragma once

#include "tz/tz_allocator.h"

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t *buffer;
    size_t capacity;
    size_t offset;
} TzArena;

void tz_arena_init(TzArena *arena, uint8_t *backingBuffer, size_t capacity);
TzAllocator tz_arena_as_allocator(TzArena *arena);
