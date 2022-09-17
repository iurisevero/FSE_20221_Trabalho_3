#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "dht11.h"
#include "freertos/semphr.h"
#define GPIO_PORT GPIO_NUM_18


void getTemperatureAndHumidity(int *temperature, int *humidity){
    DHT11_init(GPIO_PORT);
    *temperature = DHT11_read().temperature;
    *humidity = DHT11_read().humidity;
}