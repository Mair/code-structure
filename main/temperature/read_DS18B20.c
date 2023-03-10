#include "esp_log.h"
#include <ds18x20.h>

#define TAG "READ DS18B20"

float read_DS18B20(gpio_num_t pin)
{
    ds18x20_addr_t addrs[1];
    size_t sensor_count = 1;
    esp_err_t err = ds18x20_scan_devices(pin, addrs, 1, &sensor_count);
    if (err)
    {
        ESP_LOGE(TAG, "Failed to read sensor %s", esp_err_to_name(err));
        return 0;
    }
    float temperature = 0;
    ds18x20_measure_and_read(pin, addrs[0], (float *)&temperature);
    return temperature;
}
