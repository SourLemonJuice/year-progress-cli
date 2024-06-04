#include "main.h"

int main(int argc, char *argv[])
{
    /* init config structure */
    struct config_struct config_struct;
    init_config_struct(&config_struct);

    /* handle cli flags */
    if(argc > 1)
    {
        for(int i = 1; i <= argc; i++)
        {
            /* parsing flags */
            // --version
            if(not strcmp(argv[i], "--version"))
            {
                puts(APP_VERSION_STRING);
                goto APP_ERROR_OK;
            }
            // --help
            if(not strcmp(argv[i], "--help"))
            {
                puts("help? you need help me.");
                puts("--version | --max_width <uint without zero>");
                goto APP_ERROR_OK;
            }
            // --max_width
            if(not strcmp(argv[i], "--max_width"))
            {
                i++; // shift argc
                // get arg, with error check
                int width_get = atoi(argv[i]); // TODO change to a safe function please
                if(width_get <= 0) // TODO is this useful?
                {
                    puts("--max_width <num> variable invalid");
                    goto APP_ERROR_GET_OPTIONS;
                }
                config_struct.max_progress_bar_width = width_get;
                continue;
            }
            /* parsing arguments here? */
            /* Default */
            puts("Invalid flags/arguments");
            assert(false);
            goto APP_ERROR_GET_OPTIONS;
        }
    }

    /* start init */
    // Get local time
    time_t time_type = time(NULL);
    struct tm tm = *localtime(&time_type);
    // Is the leap year?
    uint16_t days_of_year;
    if((tm.tm_year + 1900) % 4 == 0)
        days_of_year = 366; // leap
    else
        days_of_year = 365; // normal

    // Get percent of year
    float year_percent = (float)tm.tm_yday / days_of_year;
    printf("This year has lost %d/%d days. That's already %f%\n", tm.tm_yday, days_of_year, year_percent);

    // Print something
    printf("[");
    uint8_t max_width = 48;
    // max_width need minus two "[]" char
    for (int i = 0; i < max_width - 2; i++)
    {
        if(i <= max_width * year_percent)
            printf("=");
        else
            printf("|");
    }
    printf("]\n");

    /* all return */
    APP_ERROR_OK:
    return APP_ERROR_OK;
    APP_ERROR_GET_OPTIONS:
    puts("Error: Break when Getting Configuration");
    return APP_ERROR_GET_OPTIONS;
}

// init config structure
int init_config_struct(struct config_struct *config)
{
    config->max_progress_bar_width = 48;

    return 0;
}
