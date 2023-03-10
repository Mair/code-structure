#include <stdio.h>
#include "driver/gpio.h"

#define HEATER_PIN 18

bool _heater_is_on = false;

void heater_init(void)
{
    gpio_set_direction(HEATER_PIN, GPIO_MODE_OUTPUT);
    gpio_pullup_en(HEATER_PIN);
    gpio_pulldown_dis(HEATER_PIN);
}

void heater_on(void)
{
    gpio_set_level(HEATER_PIN, 1);
    _heater_is_on = true;
}

void heater_off(void)
{
    gpio_set_level(HEATER_PIN, 0);
    _heater_is_on = false;
}

bool heater_is_on(void)
{
    return _heater_is_on;
}