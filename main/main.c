#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "app_config.h"
#include "temperature.h"
#include "water_control.h"

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    app_config_init();
    water_control_init();

    measure_temperature_init();

    /// @test - to remove////////
    heater_on();
    cooler_on();
    vTaskDelay(pdMS_TO_TICKS(2000));
    heater_off();
    cooler_off();
    ///////
}
