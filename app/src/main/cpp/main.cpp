#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>

#include "logging.h"
#include "Renderer.h"

extern "C" {
    #include <game-activity/native_app_glue/android_native_app_glue.c>

    void on_app_cmd(android_app *app, int32_t cmd){
        switch (cmd) {
            case APP_CMD_INIT_WINDOW:
                LOGI("Initializing the window...");
                app->userData = new Renderer(app);
                break;
            case APP_CMD_TERM_WINDOW: {
                LOGI("Terminating the window...");
                Renderer *renderer = (Renderer *) app->userData;
                if (renderer) delete renderer;
            }
                break;
            default:
                break;
        }
    }
    void android_main(android_app *app){
        app->onAppCmd = on_app_cmd;
        android_poll_source *poll_source;
        int events;

        do {
            if (ALooper_pollOnce(0, nullptr, &events, (void**) &poll_source) >= 0){
                if (poll_source) poll_source->process(app, poll_source);
            }

            if (!app->userData) continue;

            Renderer *renderer = (Renderer*) app->userData;
            renderer->do_frame();
        } while(!app->destroyRequested);
    }
}
