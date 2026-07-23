#include "tz/tz_arena.h"
#include "tz/tz_allocator.h"
#include "tz/tz_defines.h"
#include "tz/tz_memory.h"

#include <stdint.h>
#include <string.h>

static void *tz_arena_alloc_func(void *allocatorState, TzAllocator_Mode mode, size_t size,
                                 size_t alignment, void *oldMemory, size_t oldSize)

{
    TZ_UNUSED(oldMemory);
    TZ_UNUSED(oldSize);

    TzArena *arena = (TzArena *)allocatorState;

    switch (mode) {
    case TZ_ALLOC_MODE_ALLOC: {

        uintptr_t currentPointer = (uintptr_t)arena->buffer + (uintptr_t)arena->offset;
        uintptr_t alignedOffset = align_forward(currentPointer, alignment);

        alignedOffset -= (uintptr_t)arena->buffer;

        if (alignedOffset + size <= arena->capacity) {
            void *newMemory = &arena->buffer[alignedOffset];
            arena->offset = alignedOffset + size;

            memset(newMemory, 0, size);

            return newMemory;
        }

        return NULL;
    }

    case TZ_ALLOC_MODE_FREE_ALL: {
        arena->offset = 0;
        return NULL;
    }

    case TZ_ALLOC_MODE_RESIZE:
    case TZ_ALLOC_MODE_FREE:
        return NULL;
    }
}

void tz_arena_init(TzArena *arena, uint8_t *backingBuffer, size_t capacity) {
    arena->buffer = backingBuffer;
    arena->capacity = capacity;
    arena->offset = 0;
}

TzAllocator tz_arena_as_allocator(TzArena *arena) {
    return (TzAllocator){
        .state = (void *)arena,
        .alloc_function = tz_arena_alloc_func,
    };
}
