#include <stdio.h>
#include "nvs_flash.h"
#include "app_config.h"
#include "measure_water_temperature.h"
#include "measure_air_temperature.h"

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    app_config_init();

    measure_water_temperature_init();
    measure_air_temperature_init();
}
