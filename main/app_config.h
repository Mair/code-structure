#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <stdint.h>

typedef struct water_measure_t
{
    int temperature_intervale;
} water_measure_t;
typedef struct app_config_t
{
    water_measure_t water_measure;
} app_config_t;

extern app_config_t *app_config;

void app_config_init(void);
void update_config(app_config_t *new_config_app);

#endif