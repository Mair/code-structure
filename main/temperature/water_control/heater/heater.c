#include <stdio.h>
#include "driver/gpio.h"

#define HEATER_PIN 18
void heater_init(void)
{
    gpio_set_direction(HEATER_PIN, GPIO_MODE_OUTPUT);
    gpio_pullup_en(HEATER_PIN);
    gpio_pulldown_dis(HEATER_PIN);
}

void heater_on(void)
{
    gpio_set_level(HEATER_PIN, 1);
}

void heater_off(void)
{
    gpio_set_level(HEATER_PIN, 0);
}