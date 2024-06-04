// hum...
#pragma once

/* Headers */
#include <stdbool.h>
#include <iso646.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

/* Defines */
#define APP_VERSION_STRING "develop"

/* Structures */
struct config_struct
{
    uint16_t max_progress_bar_width;
};

/* Error Type */
enum APP_ERROR_ENUM
{
    APP_ERROR_OK = 0,
    APP_ERROR_STANDARD,
    APP_ERROR_GET_OPTIONS,
    APP_ERROR_DISPLAY,
};

/* Function prototypes */
int main(int argc, char *argv[]);
int init_config_struct(struct config_struct *config);
