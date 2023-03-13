#include <stdbool.h>
#include "esp_err.h"

esp_err_t divide_2_numbers(int left, int right, float *result)
{
    int local_result;
    bool is_err;
    if (right == 0)
        is_err = true;
    else
        is_err = false;

    if (is_err != 0)
    {
        local_result = left / right;
        *result = local_result;
        return ESP_OK;
    }
    return ESP_FAIL;
}

esp_err_t divide_2_numbers(int left, int right, float *result)
{
    if (right == 0)
        return ESP_FAIL;
    int local_result = left / right;
    *result = local_result;
    return ESP_OK;
}