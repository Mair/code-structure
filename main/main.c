#include <stdio.h>
#include "nvs_flash.h"
#include "app_config.h"
#include "temperature.h"
#include "water_level.h"

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    app_config_init();

    measure_temperature_init();
    init_water_level();
}
