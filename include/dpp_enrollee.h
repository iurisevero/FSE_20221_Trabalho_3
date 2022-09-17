#ifndef _DPP_H_
#define _DPP_H_

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_dpp.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "qrcodegen.h"

static void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
void dpp_enrollee_event_cb(esp_supp_dpp_event_t event, void *data);
void dpp_enrollee_init(void);
static void printQr(const uint8_t qrcode[]);

#endif