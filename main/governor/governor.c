#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "temperature.h"
#include "water_control.h"
#include "app_config.h"
#include "alerts.h"

#define TAG "governor"

static void governor_task(void *params);

void governor_init(void)
{
    xTaskCreate(governor_task, "governor_task", 1024 * 4, NULL, 5, NULL);
}

static void governor_task(void *params)
{
    while (true)
    {
        float water_temperature = get_water_temperature();

        thresholds_t thresholds = app_config->temperature.thresholds;
        if (water_temperature >= thresholds.cooler_on)
            cooler_on();
        if (water_temperature <= thresholds.cooler_off)
            cooler_off();

        if (water_temperature <= thresholds.heater_on)
            heater_on();
        if (water_temperature > thresholds.heater_off)
            heater_off();

        ///////////////// Alerts //////////////
        alert_payload_t alert_payload;
        memset(&alert_payload, 0, sizeof(alert_payload_t));
        alert_payload.air_temperature = get_air_temperature();
        alert_payload.water_temperature = get_water_temperature();

        if (water_temperature >= thresholds.alert_to_hot)
        {
            alert_payload.alert_type = WATER_TEMPERATURE_TOO_HOT;
            send_alert(&alert_payload);
        }

        if (water_temperature <= thresholds.alert_to_cold)
        {
            alert_payload.alert_type = WATER_TEMPERATURE_TOO_COLD;
            send_alert(&alert_payload);
        }

        vTaskDelay(pdMS_TO_TICKS(app_config->governor.idol_time));
    }
}
