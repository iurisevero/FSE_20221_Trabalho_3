// Referência: https://gitlab.com/fse_fga/esp32/mqtt/-/tree/master/main
#ifndef MQTT_H
#define MQTT_H

void mqtt_start();

void mqtt_envia_mensagem(char * topico, char * mensagem);

#endif