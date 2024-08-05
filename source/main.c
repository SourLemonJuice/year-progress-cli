#include "main.h"

#include <iso646.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// init config structure
static int InitConfigStruct_(struct config_struct *config)
{
    config->max_progress_bar_width = 0.6 * 80;

    return 0;
}

int main(int argc, char *argv[])
{
    /* init config structure */
    struct config_struct config;
    InitConfigStruct_(&config);

    /* handle cli flags */
    for (int i = 1; i < argc; i++) {
        /* parsing flags */
        // --version
        if (not strcmp(argv[i], "--version")) {
            printf("Version: %s\n", APP_VERSION_STRING);
            goto APP_ERROR_OK;
        }
        // --help
        if (not strcmp(argv[i], "--help")) {
            printf("Usage: year-progress [--help] [--version] [--max-width <uint>]\n");
            printf("The --max-width doesn't allow a value less than 3\n");
            goto APP_ERROR_OK;
        }
        // --max_width
        if (not strcmp(argv[i], "--max-width")) {
            i++; // shift argc
            // get arg, with error check
            int width_get = atoi(argv[i]); // TODO change to a safe function please
            if (width_get <= 2)            // TODO is this useful?
            {
                puts("--max-width <num> variable invalid");
                goto APP_ERROR_GET_OPTIONS;
            }
            config.max_progress_bar_width = width_get;
            continue;
        }
        /* parsing arguments here? */
        /* Default */
        puts("Invalid flags/arguments");
        goto APP_ERROR_GET_OPTIONS;
    }

    /* start init */
    // Get local time
    time_t time_type = time(NULL);
    struct tm tm = *localtime(&time_type);
    // Is the leap year?
    uint16_t days_of_year;
    if ((tm.tm_year + 1900) % 4 == 0)
        days_of_year = 366; // leap
    else
        days_of_year = 365; // normal

    uint8_t been_days = tm.tm_yday + 1; // the C standard...
    // Get percent of year
    float year_ratio = (float)been_days / (float)days_of_year;
    float year_percent = year_ratio * 100;
    printf("This year has lost %d/%d days. That's already %.3f%%\n", been_days, days_of_year, year_percent);

    // Print something
    printf("[");
    // max_width need minus two "[]" char
    for (int i = 0; i < config.max_progress_bar_width - 2; i++) {
        if (i <= config.max_progress_bar_width * year_ratio)
            printf("-");
        else
            printf("#");
    }
    printf("]\n");

/* all return */
APP_ERROR_OK:
    return APP_ERROR_OK;
APP_ERROR_GET_OPTIONS:
    puts("Error: Break when Getting Configuration");
    return APP_ERROR_GET_OPTIONS;
}
