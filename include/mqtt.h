// Referência: https://gitlab.com/fse_fga/esp32/mqtt/-/tree/master/main
#ifndef MQTT_H
#define MQTT_H
#include "mqtt_client.h"

void mqtt_start();

void mqtt_envia_mensagem(char * topico, char * mensagem);

void sendRequestResponse(esp_mqtt_event_handle_t event, int new_value);

#endif