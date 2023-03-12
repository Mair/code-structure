#include <time.h>
#include "esp_sntp.h"
#include "esp_log.h"
#include "set_chip_time.h"

#define TAG "NTP_TIME"

void on_got_time(struct timeval *tv);

void print_time(long time, const char *message)
{
    setenv("TZ", "EST-10EDT-11,M10.5.0/02:00:00,M3.5.0/03:00:00", 1);
    tzset();
    struct tm *timeinfo = localtime((const time_t *)&time);

    char buffer[50];
    strftime(buffer, sizeof(buffer), "%c", timeinfo);
    ESP_LOGI(TAG, "message: %s: %s", message, buffer);
}

void set_chip_time(void)
{
    sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
    sntp_setservername(0, "pool.ntp.org");
    sntp_init();
    sntp_set_time_sync_notification_cb(on_got_time);
}

void on_got_time(struct timeval *tv)
{
    setenv("TZ", "EST-10EDT-11,M10.5.0/02:00:00,M3.5.0/03:00:00", 1);
    tzset();

    ESP_LOGI(TAG, "Current time set to %s", get_time_str());
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
