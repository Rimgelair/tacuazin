#include "tz/tz_app.h"
#include "tz/tz_string.h"

int main() {

    TzAppProps props = {.title = tz_string_from_cstring("Metroya"),
                        .dimensions = {
                            .x = 800,
                            .y = 600,

                        }};

    TzApp *app = tz_app_make(&props);
    tz_app_run(app);
    tz_app_destroy(app);

    return 0;
}
