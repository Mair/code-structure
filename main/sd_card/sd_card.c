#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h>
#include "esp_debug_helpers.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "esp_log.h"
#include "sd_card.h"
#include "chip_time.h"

#define TAG "SD_CARD"
#define BASE_PATH "/sd"
#define LOG_PATH "/sd/log.csv"

#define PIN_NUM_MISO 13
#define PIN_NUM_MOSI 14
#define PIN_NUM_CLK 26
#define PIN_NUM_CS 27

SemaphoreHandle_t file_mutex_lock;

void sd_card_init(void)
{
    file_mutex_lock = xSemaphoreCreateMutex();

    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = true,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024};
    sdmmc_card_t *card;
    const char mount_point[] = BASE_PATH;
    ESP_LOGI(TAG, "Initializing SD card");

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.slot = SPI3_HOST;
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };
    esp_err_t ret = spi_bus_initialize(host.slot, &bus_cfg, SDSPI_DEFAULT_DMA);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize bus.");
        return;
    }
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = PIN_NUM_CS;
    slot_config.host_id = host.slot;

    ESP_LOGI(TAG, "Mounting filesystem");
    ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            ESP_LOGE(TAG, "Failed to mount filesystem.");
        }
        else
        {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). ", esp_err_to_name(ret));
        }
        return;
    }
    ESP_LOGI(TAG, "Filesystem mounted");

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);
}

void log_to_card(log_payload_t *log_payload)
{
    if (!xSemaphoreTake(file_mutex_lock, pdMS_TO_TICKS(1000)))
    {
        ESP_LOGE(TAG, "Failed to obtain mutex lock");
    }
    FILE *file = fopen(LOG_PATH, "a");
    if (!file)
    {
        ESP_LOGE(TAG, "failed to open file %s %s (%d) %s", LOG_PATH, __FILE__, __LINE__, __FUNCTION__);
        xSemaphoreGive(file_mutex_lock);
        return;
    }

    char write_buffer[200];
    sprintf(write_buffer, "%s,%f,%f,%f\n", get_time_str(), log_payload->air_temperature, log_payload->water_temperature, log_payload->water_level);
    fwrite(write_buffer, strlen(write_buffer), 1, file);
    fclose(file);
    xSemaphoreGive(file_mutex_lock);
}