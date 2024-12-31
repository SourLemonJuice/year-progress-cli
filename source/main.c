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
        if (strcmp(argv[i], "--version") == 0) {
            printf("Version:\t%s\n", APP_VERSION_STRING);
            printf("Git describe:\t%s\n", APP_VERSION_DESCRIBE);
            goto APP_ERROR_OK;
        }
        // --help
        if (strcmp(argv[i], "--help") == 0) {
            printf("Usage: year-progress [--help] [--version] [--max-width <uint>]\n");
            printf("The --max-width doesn't allow a value less than 3\n");
            goto APP_ERROR_OK;
        }
        // --max_width
        if (strcmp(argv[i], "--max-width") == 0) {
            i++; // shift argc
            // get arg, with error check
            long width_get = strtol(argv[i], NULL, 10);
            if (width_get < 3) {
                puts("--max-width <num> parameter invalid");
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
    int days_of_year;
    if ((tm.tm_year + 1900) % 4 == 0)
        days_of_year = 366; // leap
    else
        days_of_year = 365; // normal

    int today = tm.tm_yday + 1; // the C standard...
    // Get lost days percent of the year
    float lost_ratio = (float)(today - 1) / (float)days_of_year;
    float lost_percent = lost_ratio * 100;

    if (days_of_year == today) {
        printf("It's the last day(%d of %d), hope you'll be batter in the New Year. awa\n", today, days_of_year);
    } else {
        printf("This year has lost %d/%d days. That's already %.3f%%\n", today - 1, days_of_year, lost_percent);
    }

    // Print something
    printf("[");
    // max_width need minus two "[]" char
    for (int i = 0; i < config.max_progress_bar_width - 2; i++) {
        if (i <= config.max_progress_bar_width * lost_ratio)
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
