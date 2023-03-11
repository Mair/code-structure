#include <stdio.h>
#include <string.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "alerts.h"
#include "esp_http_client.h"
#include "cJSON.h"
#include "app_config.h"

#define TAG "Alert"

static void alert_task(void *params);
static void get_alert_str(char *alert_type_str, alert_type_t alert_type);
static esp_err_t on_http_client_data(esp_http_client_event_t *evt);

static QueueHandle_t alert_queue;

void alert_init(void)
{
    alert_queue = xQueueCreate(10, sizeof(alert_payload_t));
    xTaskCreate(alert_task, "alert_task", 1024 * 4, NULL, 10, NULL);
}

void send_alert(alert_payload_t *alert_payload)
{
    xQueueSend(alert_queue, alert_payload, pdMS_TO_TICKS(200));
}

static void alert_task(void *params)
{
    alert_payload_t alert_payload;

    while (true)
    {
        xQueueReceive(alert_queue, &alert_payload, portMAX_DELAY);

        char alert_type_str[30];
        get_alert_str(alert_type_str, alert_payload.alert_type);

        char slack_message[200];
        sprintf(slack_message, "alert ⚠️ type: %s\nwater temperature: %f, air temperature %f", alert_type_str, alert_payload.water_temperature, alert_payload.air_temperature);

        cJSON *comms_payload = cJSON_CreateObject();
        cJSON_AddStringToObject(comms_payload, "channel", app_config->alert.slack_channel);
        cJSON_AddStringToObject(comms_payload, "text", slack_message);
        char *comms_payload_str = cJSON_Print(comms_payload);
        cJSON_Delete(comms_payload);

        esp_http_client_config_t esp_http_client_config = {
            .url = "https://slack.com/api/chat.postMessage",
            .method = HTTP_METHOD_POST,
            .event_handler = on_http_client_data};
        esp_http_client_handle_t client = esp_http_client_init(&esp_http_client_config);
        esp_http_client_set_header(client, "Content-Type", "application/json");
        esp_http_client_set_header(client, "Authorization", app_config->alert.authToken);
        esp_http_client_set_post_field(client, comms_payload_str, strlen(comms_payload_str));
        esp_err_t err = esp_http_client_perform(client);
        if (err)
        {
            ESP_LOGE(TAG, "err %s", esp_err_to_name(err));
        }
        free(comms_payload_str);
    }
}

static void get_alert_str(char *alert_type_str, alert_type_t alert_type)
{
    switch (alert_type)
    {
    case WATER_TEMPERATURE_TOO_HOT:
        strcpy(alert_type_str, "WATER_TEMPERATURE_TOO_HOT");
        break;
    case WATER_TEMPERATURE_TOO_COLD:
        strcpy(alert_type_str, "WATER_TEMPERATURE_TOO_COLD");
        break;
    case WATER_LEVEL_TOO_LOW:
        strcpy(alert_type_str, "WATER_LEVEL_TOO_LOW");
        break;
    case WATER_PUMP_ERROR:
        strcpy(alert_type_str, "WATER_PUMP_ERROR");
        break;
    case AIR_PUMP_ERROR:
        strcpy(alert_type_str, "AIR_PUMP_ERROR");
        break;
    default:
        strcpy(alert_type_str, "UNKNOWN");
    }
}

static esp_err_t on_http_client_data(esp_http_client_event_t *evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        printf("HTTP COMMS: %.*s\n", evt->data_len, (char *)evt->data);
    default:
        break;
    }
    return ESP_OK;
}
