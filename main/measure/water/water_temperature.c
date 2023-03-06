#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <esp_log.h>
#include "water_temperature.h"
#include "app_config.h"
#include "../read_DS18B20.h"

#define TAG "MEASURE WATER TEMPERATURE"
#define DS18B20_GPIO_PIN 4

static volatile float temperature;

static void measure_water_temperature(void *params);

void measure_water_temperature_init()
{
    xTaskCreate(measure_water_temperature, "measure_water_temperature", 1024 * 4, NULL, 5, NULL);
}

static void measure_water_temperature(void *params)
{
    while (true)
    {
        temperature = read_DS18B20(DS18B20_GPIO_PIN);
        ESP_LOGI(TAG, "Water temperature: %f", get_water_temperature());

        vTaskDelay(pdMS_TO_TICKS(app_config->water_measure.temperature_intervale));
    }
}

float get_water_temperature(void)
{
    return temperature;
}