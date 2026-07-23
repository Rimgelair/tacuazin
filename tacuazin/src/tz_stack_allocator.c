#include "tz/tz_stack_allocator.h"
#include "tz/tz_allocator.h"
#include "tz/tz_defines.h"
#include "tz/tz_memory.h"

#include <stdint.h>
#include <string.h>

static void *tz_stack_allocator_alloc_func(void *allocatorState, TzAllocator_Mode mode, size_t size,
                                           size_t alignment, void *oldMemory, size_t oldSize)

{
    TZ_UNUSED(oldMemory);
    TZ_UNUSED(oldSize);

    TzStackAllocator *allocator = (TzStackAllocator *)allocatorState;

    switch (mode) {
    case TZ_ALLOC_MODE_ALLOC: {

        uintptr_t currentPointer = (uintptr_t)allocator->buffer + (uintptr_t)allocator->offset;
        uintptr_t alignedOffset = align_forward(currentPointer, alignment);

        alignedOffset -= (uintptr_t)allocator->buffer;

        if (alignedOffset + size <= allocator->capacity) {
            void *newMemory = &allocator->buffer[alignedOffset];
            allocator->offset = alignedOffset + size;

            memset(newMemory, 0, size);

            return newMemory;
        }

        return NULL;
    }

    case TZ_ALLOC_MODE_FREE_ALL: {
        allocator->offset = 0;
        return NULL;
    }

    case TZ_ALLOC_MODE_RESIZE:
    case TZ_ALLOC_MODE_FREE:
        return NULL;
    }
}

void tz_stack_allocator_init(TzStackAllocator *allocator, uint8_t *backingBuffer, size_t capacity) {
    allocator->buffer = backingBuffer;
    allocator->capacity = capacity;
    allocator->offset = 0;
}

TzAllocator tz_stack_allocator_as_allocator(TzStackAllocator *allocator) {
    return (TzAllocator){
        .state = (void *)allocator,
        .alloc_function = tz_stack_allocator_alloc_func,
    };
}
