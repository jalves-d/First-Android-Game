#pragma once

#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "LOG", __VA_ARGS__);
