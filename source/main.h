// hum...
#pragma once

#include <stdint.h>

/* Defines */
#ifndef APP_VERSION_STRING
    #define APP_VERSION_STRING "[Error: Version string undefined]"
#endif

/* Structures */
struct config_struct {
    uint16_t max_progress_bar_width;
};

/* Error Type */
enum APP_ERROR_ENUM {
    APP_ERROR_OK = 0,
    APP_ERROR_STANDARD,
    APP_ERROR_GET_OPTIONS,
    APP_ERROR_DISPLAY,
};
