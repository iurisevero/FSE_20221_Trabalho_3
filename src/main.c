// ReferĂȘncia: https://gitlab.com/fse_fga/esp32/mqtt/-/tree/master/main
#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "dht11.h"
#include "freertos/semphr.h"
#include "dth11_connection.h"
#include "esp_sleep.h"
#include "esp32/rom/uart.h"
#include "shock_connection.h"

#include "nvs_rw.h"
#include "wifi_helper.h"
#include "http_client.h"
#include "mqtt.h"
#include "led_connection.h"
#define SHOCK_GPIO_DIGITAL_PORT 19
#include "utils.h"
// #include "ota.h"

#define TEMPERATURE_SENSOR_ACTIVE 1
#define BOTAO_BOOT 0

#ifndef CONFIG_BATTERY_MODE
#define BATTERY_MODE 0
#else
#define BATTERY_MODE 1
#endif

xSemaphoreHandle conexaoWifiSemaphore;
xSemaphoreHandle conexaoMQTTSemaphore;

void conectadoWifi(void *params)
{
  while (true)
  {
    if (xSemaphoreTake(conexaoWifiSemaphore, portMAX_DELAY))
    {
      // Processamento Internet
      mqtt_start();
      // xTaskCreate(&start_server, "OTA Web server", 4096, NULL, 1, NULL);
    }
  }
}

void handleDHT11()
{
  char mensagem[50];
  int ledStatus = 1;
  sprintf(mensagem, "{\"turnLed\": %d}", ledStatus);
  mqtt_envia_mensagem("v1/devices/me/attributes", mensagem);
  while (true)
  {
    if (TEMPERATURE_SENSOR_ACTIVE)
    {
      int temperature, humidity;
      getTemperatureAndHumidity(&temperature, &humidity);
      printf("Temperature is %d \n", temperature);
      printf("Humidity is %d\n", humidity);
      sprintf(mensagem, "{\"temperatura\": %d, \"umidade\": %d}", temperature, humidity);
      mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);
    }
    int shock_impact;
    getDigitalOutput(&shock_impact);
    printf("Value: %d\n", shock_impact);
    if (shock_impact == 1)
    {
      SENSOR_COUNT = (SENSOR_COUNT + 1);
      write_uint32_t_nvs(NVS_NS, NVS_COUNT_KEY, &SENSOR_COUNT);
    }
    sprintf(mensagem, "{\"impacto\": %d, \"impacto_count\": %d}", shock_impact, SENSOR_COUNT);
    mqtt_envia_mensagem("v1/devices/me/attributes", mensagem);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  sprintf(mensagem, "{\"turnLed\": %d}", ledStatus);
  mqtt_envia_mensagem("v1/devices/me/attributes", mensagem);
  ledStatus = !ledStatus;
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void trataComunicacaoComServidor(void *params)
{
  while (true)
  {
    if (xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
    {
      xTaskCreate(&pwm_led, "PWM LED", 4096, NULL, 1, NULL);
      xTaskCreate(&handleDHT11, "DHT11 Handler", 4096, NULL, 1, NULL);
    }
  }
}

void app_main(void)
{
  // Inicializa o NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  checkNVSData();

  while (BATTERY_MODE)
  {
    printf("Battery Mode activated\n");
    // ConfiguraĂ§ĂŁo da GPIO para o botĂŁo de entrada
    gpio_pad_select_gpio(BOTAO_BOOT);
    gpio_set_direction(BOTAO_BOOT, GPIO_MODE_INPUT);
    gpio_wakeup_enable(BOTAO_BOOT, GPIO_INTR_LOW_LEVEL);
    gpio_pad_select_gpio(SHOCK_GPIO_DIGITAL_PORT);
    gpio_set_direction(SHOCK_GPIO_DIGITAL_PORT, GPIO_MODE_INPUT);
    gpio_wakeup_enable(SHOCK_GPIO_DIGITAL_PORT, GPIO_INTR_LOW_LEVEL);
    esp_sleep_enable_gpio_wakeup();

    // Entra em modo Light Sleep
    esp_light_sleep_start();

    wifi_start();
    if (xSemaphoreTake(conexaoWifiSemaphore, portMAX_DELAY))
    {
      // Processamento Internet
      mqtt_start();
      if (xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
      {
        char mensagem[50];
        sprintf(mensagem, "{\"turnLed\": %d}", 1);
        mqtt_envia_mensagem("v1/devices/me/attributes", mensagem);
      }
    }
  }

  conexaoWifiSemaphore = xSemaphoreCreateBinary();
  conexaoMQTTSemaphore = xSemaphoreCreateBinary();
  wifi_start();

  xTaskCreate(&conectadoWifi, "ConexĂŁo ao MQTT", 4096, NULL, 1, NULL);
  xTaskCreate(&trataComunicacaoComServidor, "ComunicaĂ§ĂŁo com Broker", 4096, NULL, 1, NULL);
}
