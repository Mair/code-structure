#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <stdint.h>

typedef struct wifi_t
{
    char ssid[30];
    char pass[30];
} wifi_t;
typedef struct governor_t
{
    int idol_time;
} governor_t;

typedef struct alert_t
{
    char slack_channel[20];
    char authToken[70];
} alert_t;

typedef struct thresholds_t
{
    float heater_on;
    float heater_off;
    float cooler_on;
    float cooler_off;
    float alert_to_hot;
    float alert_to_cold;
} thresholds_t;
typedef struct temperature_t
{
    int intervale;
    thresholds_t thresholds;
} temperature_t;
typedef struct app_config_t
{
    wifi_t wifi;
    governor_t governor;
    temperature_t temperature;
    alert_t alert;
} app_config_t;

extern app_config_t *app_config;

void app_config_init(void);
void update_config(app_config_t *new_config_app);

#endif