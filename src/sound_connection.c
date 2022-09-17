// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/gpio.h"
// #include "sdkconfig.h"
// #include "driver/adc.h"
// #include "esp_adc_cal.h"
// #include "sound_connection.h"
// #define SOUND_GPIO_DIGITAL_PORT 19
// #define SOUND_GPIO_ANALOGIC_PORT 4


// void setup(){
//     gpio_pad_select_gpio(SOUND_GPIO_DIGITAL_PORT);
//     gpio_set_direction(SOUND_GPIO_DIGITAL_PORT, GPIO_MODE_INPUT);
//     gpio_pullup_en(SOUND_GPIO_DIGITAL_PORT);

//     adc2_config_channel_atten(ADC2_CHANNEL_2, ADC_ATTEN_DB_11);
//     esp_adc_cal_characteristics_t adc2_chars;
// }

// void getAnalogicOutput(int *output){
//     *output = gpio_get_level(SOUND_GPIO_ANALOGIC_PORT);
// }

// void getDigitalOutput(int *output){
//     int raw_value = adc1_get_raw(ADC2_CHANNEL_2);
//     *output = raw_value;
// }