#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "shock_connection.h"
#define SHOCK_GPIO_DIGITAL_PORT 19



void setup(){
    gpio_pad_select_gpio(SHOCK_GPIO_DIGITAL_PORT);
    gpio_set_direction(SHOCK_GPIO_DIGITAL_PORT, GPIO_MODE_INPUT);
    gpio_pulldown_en(SHOCK_GPIO_DIGITAL_PORT);
}

void getDigitalOutput(int *output){
    *output = gpio_get_level(SHOCK_GPIO_DIGITAL_PORT);
}
