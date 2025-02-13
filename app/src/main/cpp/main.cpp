#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>

#include <android/log.h>

extern "C" {
    #include <game-activity/native_app_glue/android_native_app_glue.c>

    void on_app_cmd(android_app *app, int32_t cmd){
        switch (cmd) {
            case APP_CMD_INIT_WINDOW:
                __android_log_print(ANDROID_LOG_INFO, "LOG",
                                    "Initializing the window...");
                break;
            case APP_CMD_TERM_WINDOW:
                __android_log_print(ANDROID_LOG_INFO, "LOG",
                                    "Terminating the window...");
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
            while (ALooper_pollOnce(0, nullptr, &events, (void**) &poll_source)){
                if (poll_source) poll_source->process(app, poll_source);
            }
        } while(!app->destroyRequested);
    }
}
