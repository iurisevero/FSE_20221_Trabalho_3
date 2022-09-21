#ifndef UTILS_H
#define UTILS_H

#include <string.h>

#define NVS_NS "NVS_data"
#define NVS_PWM_KEY "PWM"

extern uint8_t LED_PWM_VALUE;
void checkNVSData();

#endif