#ifndef SET_CHIP_TIME_H
#define SET_CHIP_TIME_H

void set_chip_time();
char *get_time_str(void);
esp_err_t wait_for_time_to_be_set(int time_out);
#endif