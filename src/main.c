// Referência: https://gitlab.com/fse_fga/esp32/mqtt/-/tree/master/main
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
#include "sound_connection.h"
#include "esp_sleep.h"
#include "esp32/rom/uart.h"

#include "wifi.h"
// #include "wifi_smart_config.h"
#include "http_client.h"
#include "mqtt.h"
#include "led_connection.h"
#include "utils.h"
// #include "ota.h"

#define TEMPERATURE_SENSOR_ACTIVE 0
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
  int ledStatus = 0;
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
    sprintf(mensagem, "{\"turnLed\": %d}", ledStatus);
    mqtt_envia_mensagem("v1/devices/me/attributes", mensagem);
    ledStatus = !ledStatus;
    vTaskDelay(3000 / portTICK_PERIOD_MS);
  }
}

void trataComunicacaoComServidor(void *params)
{
  while(true)
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
    // Configuração da GPIO para o botão de entrada
    gpio_pad_select_gpio(BOTAO_BOOT);
    gpio_set_direction(BOTAO_BOOT, GPIO_MODE_INPUT);
    // Habilita o botão para acordar a placa
    gpio_wakeup_enable(BOTAO_BOOT, GPIO_INTR_LOW_LEVEL);
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
        printf("TODO Correta detecção e envio do estado da entrada ao servidor central\n"); 
      }
    }

  }

  conexaoWifiSemaphore = xSemaphoreCreateBinary();
  conexaoMQTTSemaphore = xSemaphoreCreateBinary();
  wifi_start();
  // initialise_wifi();

  xTaskCreate(&conectadoWifi, "Conexão ao MQTT", 4096, NULL, 1, NULL);
  xTaskCreate(&trataComunicacaoComServidor, "Comunicação com Broker", 4096, NULL, 1, NULL);
}
