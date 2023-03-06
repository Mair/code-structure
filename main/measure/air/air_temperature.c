#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <ds18x20.h>
#include <esp_log.h>
#include "air_temperature.h"
#include "app_config.h"

#define TAG "MEASURE AIR TEMPERATURE"
#define DS18B20_GPIO_PIN 4

static volatile float temperature;

static void measure_air_temperature(void *params);
static void get_DS18B20_reading(void);

void measure_air_temperature_init()
{
    xTaskCreate(measure_air_temperature, "measure_air_temperature", 1024 * 4, NULL, 5, NULL);
}

static void measure_air_temperature(void *params)
{
    while (true)
    {
        get_DS18B20_reading();
        ESP_LOGI(TAG, "Water temperature: %f", get_air_temperature());

        // delay should go into the config
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void get_DS18B20_reading(void)
{
    ds18x20_addr_t addrs[1];
    size_t sensor_count = 0;
    esp_err_t err = ds18x20_scan_devices(DS18B20_GPIO_PIN, addrs, 1, &sensor_count);
    if (err)
    {
        ESP_LOGE(TAG, "Failed to read sensor %s", esp_err_to_name(err));
        return;
    }
    ds18x20_measure_and_read(DS18B20_GPIO_PIN, addrs[0], (float *)&temperature);
}

float get_air_temperature(void)
{
    return temperature;
}