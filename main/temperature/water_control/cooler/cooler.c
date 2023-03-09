#include <stdio.h>
#include "driver/gpio.h"

#define WATER_PIN 19

void cooler_init(void)
{
    gpio_set_direction(WATER_PIN, GPIO_MODE_OUTPUT);
    gpio_pullup_en(WATER_PIN);
    gpio_pulldown_dis(WATER_PIN);
}

void cooler_on(void)
{
    gpio_set_level(WATER_PIN, 1);
}

void cooler_off(void)
{
    gpio_set_level(WATER_PIN, 0);
}