#include "main.h"

#include <assert.h>
#include <iso646.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "argpx/argpx.h"

#define YP_PREFIX "year-progress: "

/* Error Type */
enum APP_ERROR_ENUM {
    kExitOk = 0,
    kExitFailure,
    kExitGetOptions,
    kExitDisplay,
};

/* Structures */
struct Config {
    int progress_width;
};

// init config structure
static int InitConfigStruct_(struct Config *config)
{
    config->progress_width = 0.6 * 80;

    return 0;
}

static void CbPrintHelp_()
{
    printf("Usage: year-progress [--help] [--version] [--width <num>]\n");
    printf("The --width doesn't allow a value less than 3\n");
    exit(kExitOk);
}

static void CbPrintVersion_()
{
    printf("Version:\t%s\n", APP_VERSION_STRING);
    printf("Git describe:\t%s\n", APP_VERSION_DESCRIBE);
    exit(kExitOk);
}

static void CbWidthCheck_(void *out_in, void *param_in)
{
    struct ArgpxOutParamSingle *out = out_in;

    if (*(int *)out->var_ptr < 3) {
        fprintf(stderr, YP_PREFIX "width less than 3\n");
        exit(kExitGetOptions);
    }
}

/*
    return negative: error
*/
static int ParseArg_(int argc, char *argv[], struct Config *config)
{
    assert(config != NULL);

    int ret = 0;

    // clang-format off

    struct ArgpxStyle style = ARGPX_STYLE_INIT;
    ArgpxGroupAppend(&style, ARGPX_GROUP_GNU);  // idx 0
    ArgpxGroupAppend(&style, ARGPX_GROUP_UNIX); // idx 1

    ArgpxSymbolAppend(&style, ARGPX_SYMBOL_STOP_PARSING("--"));

    struct ArgpxFlagSet flag = ARGPX_FLAGSET_INIT;
    ArgpxFlagAppend(&flag, &(struct ArgpxFlag){
        .group_idx = 0,
        .name = "help",
        .action_type = kArgpxActionCallbackOnly,
        .callback = CbPrintHelp_,
    });
    ArgpxFlagAppend(&flag, &(struct ArgpxFlag){
        .group_idx = 0,
        .name = "version",
        .action_type = kArgpxActionCallbackOnly,
        .callback = CbPrintVersion_,
    });
    ArgpxFlagAppend(&flag, &(struct ArgpxFlag){
        .group_idx = 0,
        .name = "width",
        .action_type = kArgpxActionParamSingle,
        .action_load.param_single = {.type = kArgpxVarInt, .var_ptr = &config->progress_width},
        .callback = CbWidthCheck_,
    });

    // clang-format on

    struct ArgpxResult result;
    if (ArgpxParse(&result, argc - 1, argv + 1, &style, &flag, NULL) != kArgpxStatusSuccess) {
        fprintf(stderr, YP_PREFIX "parsing arg error[%d]: %s\n", result.status, ArgpxStatusString(result.status));
        fprintf(stderr, "Error arg: %s\n", result.current_argv_ptr);
        ret = -1;
        goto out;
    }

    if (result.param_c > 0) {
        fprintf(stderr, YP_PREFIX "non-flag arguments no needed\n");
        ret = -1;
        goto out;
    }

out:
    ArgpxStyleFree(&style);
    ArgpxFlagFree(&flag);
    ArgpxResultFree(&result);
    return ret;
}

int main(int argc, char *argv[])
{
    /* init config structure */
    struct Config config;
    InitConfigStruct_(&config);

    if (ParseArg_(argc, argv, &config) < 0)
        exit(kExitGetOptions);

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
    // Get current days percent of the year
    float days_ratio = (float)today / (float)days_of_year;
    float days_percent = days_ratio * 100;

    if (days_of_year == today) {
        printf("It's the last day(%d of %d), hope you'll be batter in the New Year. awa\n", today, days_of_year);
    } else {
        printf("It's day %d of the year(%d). That's already %.1f%%\n", today, days_of_year, days_percent);
    }

    // Print something
    printf("[");
    // max_width need minus two "[]" char
    for (int i = 0; i < config.progress_width - 2; i++) {
        if (i <= config.progress_width * days_ratio)
            printf("-");
        else
            printf("#");
    }
    printf("]\n");

    return kExitOk;
}
