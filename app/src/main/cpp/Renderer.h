#pragma

#include <GLES/egl.h>
#include <game-activity/native_app_glue/android_native_app_glue.h>


class Renderer {
public:
    Renderer(android_app *app);
    ~Renderer();

    void do_frame();
private:
    EGLDisplay display;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;
};
