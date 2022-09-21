#ifndef UTILS_H
#define UTILS_H

#include <string.h>

#define NVS_NS "NVS_data"
#define NVS_PWM_KEY "PWM"
#define NVS_SSID_KEY "SSID"
#define NVS_PASWD_KEY "PASWD"

extern uint8_t LED_PWM_VALUE;
void checkNVSData();

#endif