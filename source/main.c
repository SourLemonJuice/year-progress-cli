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
    uint16_t max_days;
    if((tm.tm_year + 1900) % 4 == 0)
        max_days = 366; // leap
    else
        max_days = 365; // normal

    // Get percent
    float year_percent = (float)tm.tm_yday / max_days;
    printf("This year has lost %d days. That's already %f%\n", tm.tm_yday, year_percent);

    // Print something
    uint8_t max_width = 48;
    for (int i = 0; i < max_width; i++)
    {
        if(i <= max_width * year_percent)
            printf("=");
        else
            printf("|");
    }
    printf("\n");
    

    return 0;
}
