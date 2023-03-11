#ifndef ALERT_H
#define ALERT_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

typedef enum alert_types_t
{
    WATER_TEMPERATURE_TOO_HOT,
    WATER_TEMPERATURE_TOO_COLD,
    WATER_LEVEL_TOO_LOW,
    WATER_PUMP_ERROR,
    AIR_PUMP_ERROR
} alert_type_t;

typedef struct alert_payload_t
{
    alert_type_t alert_type;
    float water_temperature;
    float air_temperature;
    // other members here
} alert_payload_t;

void alert_init(void);
void send_alert(alert_payload_t *alert_payload);

#endif