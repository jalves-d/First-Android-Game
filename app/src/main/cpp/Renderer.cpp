#include "Renderer.h"
#include "logging.h"
#include <cassert>
#include <GLES/egl.h>

Renderer::Renderer(android_app *app) {
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    assert(display);

    auto res = eglInitialize(display, nullptr, nullptr);
    assert(res == EGL_TRUE);
    {
        EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_RED_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_NONE,
        };

        EGLint num_configs;
        eglChooseConfig(display, attribs, &config, 1, &num_configs);
        assert(num_configs == 1);
    }

    surface = eglCreateWindowSurface(display, config, app->window, nullptr);
    assert(surface != EGL_NO_SURFACE);

    {
        EGLint attribs[] = {
                EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE,
        };
        context = eglCreateContext(display, config, nullptr, attribs);
        assert(context != EGL_NO_CONTEXT);
    }

    res = eglMakeCurrent(display, surface, surface, context);
    assert(res);

    LOGI("EGL initialization is complete.")

    glClearColor(1.f, 1.f, 0.f, 1.f);
}

Renderer::~Renderer() {
    eglDestroyContext(display, context);
    eglDestroySurface(display, surface);
    eglTerminate(display);
}

void Renderer::do_frame() {
    int widht, height;
    eglQuerySurface(display, surface, EGL_WIDTH, &widht);
    eglQuerySurface(display, surface, EGL_HEIGHT, &height);

    glViewport(0, 0, widht, height);
    glClear(GL_COLOR_BUFFER_BIT);

    auto res = eglSwapBuffers(display, surface);
    assert(res);
}