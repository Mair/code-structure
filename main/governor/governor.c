#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "temperature.h"
#include "water_control.h"
#include "app_config.h"

#define TAG "governor"

static void governor_task(void *params);

void governor_init(void)
{
    xTaskCreate(governor_task, "governor_task", 1024 * 4, NULL, 8, NULL);
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

        vTaskDelay(pdMS_TO_TICKS(app_config->governor.idol_time));
    }
}
