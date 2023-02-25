#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct app_config_t
{
    int thresh_upper;
    int lower_thresh;
} app_config_t;
app_config_t app_config;

void does_work()
{
    int value = get_val();
    bool cd = value > app_config.thresh_upper;
    bool ht = value < app_config.lower_thresh;

    cold(cd);
    heat(ht);
}