#include "tz/tz_app.h"
#include "tz/tz_window.h"

#include <stdlib.h>

struct TzApp {
    TzAppProps app_props;
    TzWindow *window;
};

TzApp *tz_app_make(TzAppProps *appProps) {
    TzApp *newApp = malloc(sizeof(TzApp));
    newApp->app_props = *appProps;

    newApp->window = tz_window_make(newApp->app_props.title, newApp->app_props.dimensions);

    return newApp;
}

void tz_app_run(TzApp *app) {
    while (!tz_window_should_close(app->window)) {
        tz_window_poll_events(app->window);
    }
}

void tz_app_destroy(TzApp *app) {
    tz_window_destroy(app->window);
    free(app);
}
