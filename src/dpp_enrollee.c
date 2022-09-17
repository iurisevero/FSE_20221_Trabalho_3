/* DPP Enrollee Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.

   source: https://github.com/espressif/esp-idf/blob/master/examples/wifi/wifi_easy_connect/dpp-enrollee/main/dpp_enrollee_main.c
*/
#include "dpp_enrollee.h"

#define DPP_LISTEN_CHANNEL_LIST     CONFIG_ESP_DPP_LISTEN_CHANNEL_LIST
#define DPP_BOOTSTRAPPING_KEY   CONFIG_ESP_DPP_BOOTSTRAPPING_KEY
#define DPP_DEVICE_INFO      CONFIG_ESP_DPP_DEVICE_INFO


#define CURVE_SEC256R1_PKEY_HEX_DIGITS     64

static const char *TAG = "wifi dpp-enrollee";
wifi_config_t s_dpp_wifi_config;

static int s_retry_num = 0;

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_dpp_event_group;

#define DPP_CONNECTED_BIT  BIT0
#define DPP_CONNECT_FAIL_BIT     BIT1
#define DPP_AUTH_FAIL_BIT           BIT2

static void event_handler(void *arg, esp_event_base_t event_base,
                          int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        ESP_ERROR_CHECK(esp_supp_dpp_start_listen());
        ESP_LOGI(TAG, "Started listening for DPP Authentication");
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < 5) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_dpp_event_group, DPP_CONNECT_FAIL_BIT);
        }
        ESP_LOGI(TAG, "connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_dpp_event_group, DPP_CONNECTED_BIT);
    }
}

void dpp_enrollee_event_cb(esp_supp_dpp_event_t event, void *data)
{
    switch (event) {
    case ESP_SUPP_DPP_URI_READY:
        if (data != NULL) {
            // esp_qrcode_config_t cfg = ESP_QRCODE_CONFIG_DEFAULT();
            enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;  // Error correction level
	
            // Make and print the QR Code symbol
            uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
            uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
            bool ok = qrcodegen_encodeText((const char *)data, tempBuffer, qrcode, errCorLvl,
                qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
            if (ok){
                ESP_LOGI(TAG, "Scan below QR Code to configure the enrollee:\n");
                printQr(qrcode);
            }
            // esp_qrcode_generate(&cfg, (const char *)data);
        }
        break;
    case ESP_SUPP_DPP_CFG_RECVD:
        memcpy(&s_dpp_wifi_config, data, sizeof(s_dpp_wifi_config));
        esp_wifi_set_config(ESP_IF_WIFI_STA, &s_dpp_wifi_config);
        ESP_LOGI(TAG, "DPP Authentication successful, connecting to AP : %s",
                 s_dpp_wifi_config.sta.ssid);
        s_retry_num = 0;
        esp_wifi_connect();
        break;
    case ESP_SUPP_DPP_FAIL:
        if (s_retry_num < 5) {
            ESP_LOGI(TAG, "DPP Auth failed (Reason: %s), retry...", esp_err_to_name((int)data));
            ESP_ERROR_CHECK(esp_supp_dpp_start_listen());
            s_retry_num++;
        } else {
            xEventGroupSetBits(s_dpp_event_group, DPP_AUTH_FAIL_BIT);
        }
        break;
    default:
        break;
    }
}

esp_err_t dpp_enrollee_bootstrap(void)
{
    esp_err_t ret;
    size_t pkey_len = strlen(DPP_BOOTSTRAPPING_KEY);
    char *key = NULL;

    if (pkey_len) {
        /* Currently only NIST P-256 curve is supported, add prefix/postfix accordingly */
        char prefix[] = "30310201010420";
        char postfix[] = "a00a06082a8648ce3d030107";

        if (pkey_len != CURVE_SEC256R1_PKEY_HEX_DIGITS) {
            ESP_LOGI(TAG, "Invalid key length! Private key needs to be 32 bytes (or 64 hex digits) long");
            return ESP_FAIL;
        }

        key = malloc(sizeof(prefix) + pkey_len + sizeof(postfix));
        if (!key) {
            ESP_LOGI(TAG, "Failed to allocate for bootstrapping key");
            return ESP_ERR_NO_MEM;
        }
        sprintf(key, "%s%s%s", prefix, DPP_BOOTSTRAPPING_KEY, postfix);
    }

    /* Currently only supported method is QR Code */
    ret = esp_supp_dpp_bootstrap_gen(DPP_LISTEN_CHANNEL_LIST, DPP_BOOTSTRAP_QR_CODE,
                                     key, DPP_DEVICE_INFO);

    if (key)
        free(key);

    return ret;
}

void dpp_enrollee_init(void)
{
    s_dpp_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL));

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_supp_dpp_init(dpp_enrollee_event_cb));
    ESP_ERROR_CHECK(dpp_enrollee_bootstrap());
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
     * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
    EventBits_t bits = xEventGroupWaitBits(s_dpp_event_group,
                                           DPP_CONNECTED_BIT | DPP_CONNECT_FAIL_BIT | DPP_AUTH_FAIL_BIT,
                                           pdFALSE,
                                           pdFALSE,
                                           portMAX_DELAY);

    /* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
     * happened. */
    if (bits & DPP_CONNECTED_BIT) {
        ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
                 s_dpp_wifi_config.sta.ssid, s_dpp_wifi_config.sta.password);
    } else if (bits & DPP_CONNECT_FAIL_BIT) {
        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
                 s_dpp_wifi_config.sta.ssid, s_dpp_wifi_config.sta.password);
    } else if (bits & DPP_AUTH_FAIL_BIT) {
        ESP_LOGI(TAG, "DPP Authentication failed after %d retries", s_retry_num);
    } else {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
    }

    esp_supp_dpp_deinit();
    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler));
    ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler));
    vEventGroupDelete(s_dpp_event_group);
}

// Prints the given QR Code to the console.
static void printQr(const uint8_t qrcode[]) {
	int size = qrcodegen_getSize(qrcode);
	int border = 4;
	for (int y = -border; y < size + border; y++) {
		for (int x = -border; x < size + border; x++) {
			fputs((qrcodegen_getModule(qrcode, x, y) ? "##" : "  "), stdout);
		}
		fputs("\n", stdout);
	}
	fputs("\n", stdout);
}