#ifndef SD_CARD_H
#define SD_CARD_H

typedef struct log_payload_t
{
    float water_temperature;
    float water_level;
    float air_temperature;

} log_payload_t;

void sd_card_init(void);

void log_to_card(log_payload_t *log_payload);
#endif