#pragma once

#include "tz/tz_allocator.h"

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t *buffer;
    size_t capacity;
    size_t offset;
} TzStackAllocator;

void tz_stack_allocator_init(TzStackAllocator *allocator, uint8_t *backingBuffer, size_t capacity);
TzAllocator tz_stack_allocator_as_allocator(TzStackAllocator *allocator);
