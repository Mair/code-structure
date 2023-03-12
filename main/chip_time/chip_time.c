#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_sntp.h"
#include "esp_log.h"
#include "chip_time.h"

#define TAG "NTP_TIME"
static void on_got_time(struct timeval *tv);

static EventGroupHandle_t time_events;
const int GOT_TIME = BIT0;

void set_chip_time(void)
{
    time_events = xEventGroupCreate();

    sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
    sntp_setservername(0, "pool.ntp.org");
    sntp_init();
    sntp_set_time_sync_notification_cb(on_got_time);
}

static void on_got_time(struct timeval *tv)
{
    setenv("TZ", "EST-10EDT-11,M10.5.0/02:00:00,M3.5.0/03:00:00", 1);
    tzset();

    ESP_LOGI(TAG, "Current time set to %s", get_time_str());
    xEventGroupSetBits(time_events, GOT_TIME);
}

char *get_time_str(void)
{
    static char time_buf[30];

    time_t now = 0;
    time(&now);
    struct tm *time_info = localtime((const time_t *)&now);
    strftime(time_buf, sizeof(time_buf), "%c", time_info);
    return time_buf;
}

esp_err_t wait_for_time_to_be_set(int time_out)
{
    if (xEventGroupWaitBits(time_events, GOT_TIME, false, true, pdMS_TO_TICKS(time_out)) == GOT_TIME)
    {
        return ESP_OK;
    }
    return ESP_FAIL;
}
