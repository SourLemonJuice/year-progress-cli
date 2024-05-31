#include <stdbool.h>
#include <iso646.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
    // Get local time
    time_t time_type = time(NULL);
    struct tm tm = *localtime(&time_type);

    // Is the leap year?
    uint16_t days_of_year;
    if((tm.tm_year + 1900) % 4 == 0)
        days_of_year = 366; // leap
    else
        days_of_year = 365; // normal

    // Get percent
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
    

    return 0;
}
