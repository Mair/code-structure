#include <stdlib.h>
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
        // check for alerts after testing it here

        ///////////////////////////////
        ///@test on off controls////
        heater_on();
        cooler_on();
        vTaskDelay(pdMS_TO_TICKS(2000));
        heater_off();
        cooler_off();
        ///////
        ///@test sending alerts////
        alert_payload_t alert_payload = {
            .alert_type = WATER_TEMPERATURE_TOO_HOT,
            .air_temperature = get_air_temperature(),
            .water_temperature = get_water_temperature()};
        send_alert(&alert_payload);
        ////

        vTaskDelay(pdMS_TO_TICKS(app_config->governor.idol_time));
    }
}
