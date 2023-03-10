#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "alerts.h"

#define TAG "Alert"

static void alert_task(void *params);

QueueHandle_t alert_queue;

void alert_init(void)
{
    alert_queue = xQueueCreate(10, sizeof(alert_payload_t));
    xTaskCreate(alert_task, "alert_task", 1024 * 4, NULL, 10, NULL);
}

static void alert_task(void *params)
{
    alert_payload_t alert_payload;

    while (true)
    {
        xQueueReceive(alert_queue, &alert_payload, portMAX_DELAY);

        ESP_LOGW(TAG, "received Alert %d, water temp %f\n", alert_payload.alert_type, alert_payload.water_temperature);
    }
}