#pragma once

#include <stdalign.h>
#include <stddef.h>

typedef enum {
    TZ_ALLOC_MODE_ALLOC,
    TZ_ALLOC_MODE_FREE,
    TZ_ALLOC_MODE_FREE_ALL,
    TZ_ALLOC_MODE_RESIZE
} TzAllocator_Mode;

typedef enum {
    TZ_ALLOC_ERROR_NONE,
    TZ_ALLOC_ERROR_UNSUPPORTED_OPERATION,
    TZ_ALLOC_ERROR_INSUFFICIENT_SPACE,
} TzAllocator_Error;

typedef void *(*TzAllocationFunction)(void *allocatorState, TzAllocator_Mode mode, size_t size,
                                      size_t alignment, void *oldMemory, size_t oldSize);

typedef struct {
    void *state;
    TzAllocationFunction alloc_function;
} TzAllocator;

#define tz_allocator_alloc(allocator, type)                                                        \
    ((allocator).alloc_function((allocator).state, TZ_ALLOC_MODE_ALLOC, sizeof(type),              \
                                alignof(type), NULL, 0))

#define tz_allocator_alloc_array(allocator, type, count)                                           \
    ((allocator).alloc_function((allocator).state, TZ_ALLOC_MODE_ALLOC, sizeof(type) * (count),    \
                                alignof(type), NULL, 0))

#define tz_allocator_free_all(allocator)                                                           \
    ((allocator).alloc_function((allocator).state, TZ_ALLOC_MODE_FREE_ALL, 0, 0, NULL, 0))\
