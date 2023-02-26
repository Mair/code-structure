#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct app_config_t
{
    int temperature_upper_threshold;
    int temperature_lower_threshold;
} app_config_t;
app_config_t app_config;

void does_work()
{
    int water_temperature = get_water_temperature();
    bool should_be_cooled = water_temperature > app_config.temperature_upper_threshold;
    bool should_be_heated = water_temperature < app_config.temperature_lower_threshold;

    cold(should_be_cooled);
    heat(should_be_heated);
}