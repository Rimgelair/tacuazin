#include "tz/tz_app.h"
#include "tz/tz_memory.h"
#include "tz/tz_string.h"

#include <stdio.h>

int main() {
    printf("Page size: %zu bytes\n", get_platform_page_size());

    TzAppProps props;
    props.title = tz_string_from_cstring("Metroya");
    props.dimensions.x = 800;
    props.dimensions.y = 600;

    TzApp *app = tz_app_make(&props);
    tz_app_run(app);
    tz_app_destroy(app);

    return 0;
}
