#include "utils.h"
#include "nvs_rw.h"

#include <string.h>


uint8_t LED_PWM_VALUE = 255;

uint32_t SENSOR_COUNT = 0;

void checkNVSData(){
    int ret, retries = 3;
    for(int i=0; i < retries; ++i){
        uint8_t value; 
        uint32_t count; 
        ret = read_uint8_t_nvs(NVS_NS, NVS_PWM_KEY, &value);
        if(ret == 0){
            LED_PWM_VALUE = value;
        }
        ret = read_uint32_t_nvs(NVS_NS, NVS_COUNT_KEY, &count);
        if(ret == 0){
            SENSOR_COUNT = count;
        }
    }
}

