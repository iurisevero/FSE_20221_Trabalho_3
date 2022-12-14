// ReferĂȘncia: https://gitlab.com/fse_fga/esp32/mqtt/-/tree/master/main
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_system.h"
#include "esp_event.h"
#include "esp_netif.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "utils.h"
#include "esp_log.h"
#include "mqtt_client.h"

#include "mqtt.h"
#include "utils.h"
#include "json_utils.h"
#include "led_connection.h"
#include "nvs_rw.h"

#define TAG "MQTT"
#define MQTT_URI CONFIG_MQTT_URI
#define MQTT_USERNAME CONFIG_MQTT_USERNAME

extern xSemaphoreHandle conexaoMQTTSemaphore;
esp_mqtt_client_handle_t client;

void handle_mqtt_event_data(esp_mqtt_event_handle_t event)
{
    char response[300];
    char params[30];
    char method[30];
    char mensagem[50];
    char topic[150];
    sprintf(response, "%.*s", event->data_len, event->data);
    get_response_method(response, method);
    get_response_params(response, params);
    printf("Event Method: %s(%d)\tEvent params: %s(%d)\n", method, strlen(method), params, strlen(params));
    if (strstr(method, "setTurnLed") != NULL)
    {
        int status = strstr(params, "true") != NULL ? 1 : 0;
        turn_led(status);
        sendRequestResponse(event, status);
    }
    else if (strstr(method, "setLedIntensity") != NULL)
    {
        int led_intensity = atoi(params);
        LED_PWM_VALUE = led_intensity;
        write_uint8_t_nvs(NVS_NS, NVS_PWM_KEY, &LED_PWM_VALUE);
        sendRequestResponse(event, LED_PWM_VALUE);
    }
    else if (strstr(method, "getTurnLed") != NULL)
    {
        sendRequestResponse(event, 1);
    }
    else if (strstr(method, "getLedIntensity") != NULL)
    {
        sendRequestResponse(event, LED_PWM_VALUE);
    }
}

void sendRequestResponse(esp_mqtt_event_handle_t event, int new_value)
{
    char topic[150];
    char *requestId;
    char response[200];
    char mensagem[50];
    sprintf(topic, "%.*s", event->topic_len, event->topic);
    requestId = strstr(topic, "request/") + strlen("request/");
    printf("Esse Ă© o id:%s\n", requestId);
    sprintf(response, "v1/devices/me/rpc/response/%s", requestId);
    sprintf(mensagem, "%d", new_value);
    mqtt_envia_mensagem(response, mensagem);
}

static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;

    switch (event->event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        xSemaphoreGive(conexaoMQTTSemaphore);
        msg_id = esp_mqtt_client_subscribe(client, "v1/devices/me/rpc/request/+", 0);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);

        handle_mqtt_event_data(event);
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
    return ESP_OK;
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    mqtt_event_handler_cb(event_data);
}

void mqtt_start()
{
    esp_mqtt_client_config_t mqtt_config = {
        .uri = MQTT_URI,
        .username = MQTT_USERNAME};
    client = esp_mqtt_client_init(&mqtt_config);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_mqtt_client_start(client);
}

void mqtt_envia_mensagem(char *topico, char *mensagem)
{
    int message_id = esp_mqtt_client_publish(client, topico, mensagem, 0, 1, 0);
    ESP_LOGI(TAG, "Mensagem enviada, ID: %d", message_id);
}
