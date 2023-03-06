#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <ds18x20.h>
#include <esp_log.h>
#include "air_temperature.h"
#include "app_config.h"
#include "../read_DS18B20.h"

#define TAG "MEASURE AIR TEMPERATURE"
#define DS18B20_GPIO_PIN 4

static volatile float temperature;

static void measure_air_temperature(void *params);

void measure_air_temperature_init()
{
    xTaskCreate(measure_air_temperature, "measure_air_temperature", 1024 * 4, NULL, 5, NULL);
}

static void measure_air_temperature(void *params)
{
    while (true)
    {
        temperature = read_DS18B20(DS18B20_GPIO_PIN);
        ESP_LOGI(TAG, "Water temperature: %f", get_air_temperature());

        // delay should go into the config
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

float get_air_temperature(void)
{
    return temperature;
}