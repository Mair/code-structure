#ifndef COOLER_H
#define COOLER_H

#include <stdbool.h>

void cooler_init(void);
void cooler_on(void);
void cooler_off(void);
bool cooler_is_on(void);
#endif