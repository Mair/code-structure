#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "app_config.h"
#include "esp_log.h"

app_config_t *app_config;

#define TAG "APP CONFIG"
#define APP_CONFIG_KEY "app_config"

#define MINUTE (1000 * 60)

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
        app_config_t new_app_config = {
            .measure = {
                .temperature_intervale = 5 * MINUTE}};
        update_config(&new_app_config);
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