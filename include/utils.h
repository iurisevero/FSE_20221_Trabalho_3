#ifndef UTILS_H
#define UTILS_H

#include <string.h>

#define NVS_NS "NVS_data"
#define NVS_PWM_KEY "PWM"
#define NVS_SSID_KEY "SSID"
#define NVS_PASWD_KEY "PASWD"
#define NVS_COUNT_KEY "COUNT"

extern uint8_t LED_PWM_VALUE;
extern uint32_t SENSOR_COUNT;

void checkNVSData();

#endif