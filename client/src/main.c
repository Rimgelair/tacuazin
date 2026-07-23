#include "tz/tz_allocator.h"
#include "tz/tz_app.h"
#include "tz/tz_arena.h"
#include "tz/tz_memory.h"
#include "tz/tz_string.h"

#include <stdlib.h>

int main() {

    void *backingBuffer = malloc(mib(1));

    TzArena arena;
    tz_arena_init(&arena, backingBuffer, mib(1));

    TzAllocator appAlloc = tz_arena_as_allocator(&arena);

    TzAppProps *props = (TzAppProps *)tz_allocator_alloc(appAlloc, TzAppProps);

    props->title = tz_string_from_cstring("Metroya");
    props->dimensions.x = 800;
    props->dimensions.y = 600;

    TzApp *app = tz_app_make(props);
    tz_app_run(app);
    tz_app_destroy(app);

    free(backingBuffer);

    return 0;
}
