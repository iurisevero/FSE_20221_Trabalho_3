#include <string.h>

#include "wifi_helper.h"
#include "wifi.h"
#include "wifi_smart_config.h"
#include "utils.h"
#include "nvs_rw.h"

void wifi_start(){
    char ssid[33] = { 0 };
    char password[65] = { 0 };
    size_t ssid_size = 33, password_size = 65;
    int ret = 0, retries = 3;
    for(int i=0; i < retries; ++i){
        ret = read_string_nvs(NVS_NS, NVS_SSID_KEY, ssid, &ssid_size);
        if(ret == 0) break;
    }
    for(int i=0; i < retries; ++i){
        ret = read_string_nvs(NVS_NS, NVS_PASWD_KEY, password, &password_size);
        if(ret == 0) break;
    }

    if(strlen(ssid) && strlen(password)){
        initialise_wifi(ssid, password);
    } else {
        initialise_wifi_smart();
    }

}