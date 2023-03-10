#ifndef HEATER_H
#define HEATER_H

#include <stdbool.h>

void heater_off(void);
void heater_on(void);
void heater_init(void);
bool heater_is_on(void);
#endif
