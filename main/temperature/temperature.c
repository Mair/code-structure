#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <ds18x20.h>
#include <esp_log.h>
#include "temperature.h"
#include "app_config.h"
#include "read_DS18B20.h"

#define TAG "MEASURE TEMPERATURE"
#define WATER_DS18B20_GPIO_PIN 4
#define AIR_DS18B20_GPIO_PIN 4

static volatile float water_temperature;
static volatile float air_temperature;

static void measure_temperature(void *params);

void measure_temperature_init()
{
    xTaskCreate(measure_temperature, "measure_temperature", 1024 * 4, NULL, 5, NULL);
}

static void measure_temperature(void *params)
{
    while (true)
    {
        water_temperature = read_DS18B20(WATER_DS18B20_GPIO_PIN);
        ESP_LOGI(TAG, "Water temperature: %f", get_water_temperature());

        air_temperature = read_DS18B20(AIR_DS18B20_GPIO_PIN);
        ESP_LOGI(TAG, "Air temperature: %f", get_air_temperature());

        vTaskDelay(pdMS_TO_TICKS(app_config->temperature.intervale));
    }
}

float get_air_temperature(void)
{
    return air_temperature;
}

float get_water_temperature(void)
{
    return water_temperature;
}