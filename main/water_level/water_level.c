#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "app_config.h"
#include "esp_log.h"
#include "esp_random.h"
#include "water_level.h"

#define TAG "WATER_LEVEL"

static volatile float water_level = 0;

static void water_level_task(void *params);
static void read_water_level();

void init_water_level(void)
{
    xTaskCreate(water_level_task, "water_level_task", 1024 * 4, NULL, 5, NULL);
}

static void water_level_task(void *params)
{
    while (true)
    {
        read_water_level();
        ESP_LOGI(TAG, "Water level: %f", get_water_level());
        vTaskDelay(pdMS_TO_TICKS(app_config->measure.water_level_intervale));
    }
}

static void read_water_level()
{
    // mocked for now to save time
    water_level = 120.55;
}

float get_water_level(void)
{
    return water_level;
}