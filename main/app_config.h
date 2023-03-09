#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <stdint.h>

typedef struct temperature_t
{
    int intervale;
    float threshold_heater_on;
    float threshold_heater_off;
    float threshold_cooler_on;
    float threshold_cooler_off;
    float threshold_alert_to_hot;
    float threshold_alert_to_cold;
} temperature_t;
typedef struct app_config_t
{
    temperature_t temperature;
} app_config_t;

extern app_config_t *app_config;

void app_config_init(void);
void update_config(app_config_t *new_config_app);

#endif