#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "app_config.h"
#include "esp_log.h"

app_config_t *app_config;

#define TAG "APP CONFIG"
#define APP_CONFIG_KEY "app_config"

#define MINUTE (1000 * 60)

static void app_config_default(void)
{
    app_config_t new_app_config = {
        .temperature = {
            .intervale = 5 * MINUTE,
            .thresholds = {
                .heater_on = 5.0,
                .heater_off = 6.0,
                .cooler_on = 28.0,
                .cooler_off = 26.0,
                .alert_to_cold = 3.0,
                .alert_to_hot = 30.0}},
        .governor = {.idol_time = 1 * MINUTE}};
    update_config(&new_app_config);
}

void app_config_init()
{
    app_config = malloc(sizeof(app_config_t));

    nvs_handle handle;
    nvs_open("app_config", NVS_READWRITE, &handle);
    size_t config_size = sizeof(app_config_t);
    esp_err_t err = nvs_get_blob(handle, APP_CONFIG_KEY, app_config, &config_size);
    if (err == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGW(TAG, "Initializing config into NVS");
        nvs_close(handle);
        app_config_default();
        return;
    }

    nvs_close(handle);
}

void update_config(app_config_t *new_config_app)
{
    nvs_handle handle;
    nvs_open("app_config", NVS_READWRITE, &handle);
    ESP_ERROR_CHECK(nvs_set_blob(handle, APP_CONFIG_KEY, new_config_app, sizeof(app_config_t)));
    nvs_commit(handle);
    nvs_close(handle);

    memcpy(app_config, new_config_app, sizeof(app_config_t));
}