#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct water_threshold_t
{
    int temperature_upper;
    int temperature_lower;
} water_threshold_t;
typedef struct app_config_t
{
    water_threshold_t water_threshold;
} app_config_t;
app_config_t app_config;

void cool_water()
{
    cooler_on(true);
    heater_on(false);
}

void heat_water()
{
    cooler_on(false);
    heater_on(true);
}

void water_temperature_in_range()
{
    cooler_on(false);
    heater_on(false);
}

void does_work()
{
    int water_temperature = get_water_temperature();

    water_threshold_t threshold = app_config.water_threshold;

    if (water_temperature > threshold.temperature_upper)
        cool_water();
    else if (water_temperature < threshold.temperature_lower)
        heat_water();
    else
        water_temperature_in_range();
}