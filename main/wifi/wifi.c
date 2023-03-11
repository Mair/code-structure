#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "connect.h"
#include "app_config.h"

void wifi_connect_init()
{
    wifi_init();
    printf("app_config->wifi.ssid %s, app_config->wifi.pass %s\n", app_config->wifi.ssid, app_config->wifi.pass);
    if (wifi_connect_sta(app_config->wifi.ssid, app_config->wifi.pass, 5000) != ESP_OK)
    {
        ESP_LOGE("WIFI", "Wi-Fi could not connect");
    }
}
