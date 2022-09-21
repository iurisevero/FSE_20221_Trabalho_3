#ifndef _WIFI_SMART_CONFIG_H_
#define _WIFI_SMART_CONFIG_H_

#include <string.h>
#include "esp_event.h"


static void smartconfig_example_task(void * parm);
static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data);
static void initialise_wifi(void);
static void smartconfig_example_task(void * parm);


#endif