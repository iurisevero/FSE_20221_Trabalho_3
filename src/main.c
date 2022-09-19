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

#include "wifi.h"
#include "http_client.h"
#include "mqtt.h"
#include "led_connection.h"

#define TEMPERATURE_SENSOR_ACTIVE 0

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
    }
  }
}

void trataComunicacaoComServidor(void *params)
{
  char mensagem[50];
  int ledStatus = 0;
  if (xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
  {
    while (true)
    {
      if(TEMPERATURE_SENSOR_ACTIVE){
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
}

void runLedPWM(void *params){

  if (xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
  {
    pwm_led();
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

  if(BATTERY_MODE){
    printf("Battery Mode activated\n");
  }

  conexaoWifiSemaphore = xSemaphoreCreateBinary();
  conexaoMQTTSemaphore = xSemaphoreCreateBinary();
  wifi_start();

  xTaskCreate(&conectadoWifi, "Conexão ao MQTT", 4096, NULL, 1, NULL);
  xTaskCreate(&runLedPWM, "PWM LED", 4096, NULL, 1, NULL);
  // xTaskCreate(&trataComunicacaoComServidor, "Comunicação com Broker", 4096, NULL, 1, NULL);
}
