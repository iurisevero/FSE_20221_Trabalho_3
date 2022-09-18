#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "led_connection.h"
#include "utils.h"

#define LED 2

void turn_led(int status)
{
    gpio_pad_select_gpio(LED);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);

    gpio_set_level(LED, status);
}

void pwm_led()
{
    printf("entrou");
    // Configuração do Timer
    ledc_timer_config_t timer_config = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 1000,
        .clk_cfg = LEDC_AUTO_CLK};
    ledc_timer_config(&timer_config);

    // Configuração do Canal
    ledc_channel_config_t channel_config = {
        .gpio_num = LED,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0};
    ledc_channel_config(&channel_config);

    while (true)
    {
        for (int i = 0; i < LED_PWM_VALUE; i++)
        {
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, i);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }

        for (int i = LED_PWM_VALUE; i > 0; i--)
        {
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, i);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
    }
}