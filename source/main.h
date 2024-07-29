// hum...
#pragma once

/* Headers */
#include <assert.h>
#include <iso646.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Defines */
#ifndef APP_VERSION_STRING
    #define APP_VERSION_STRING "develop"
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
