#ifndef MK_ESP32_HME_WIFI_H
#define MK_ESP32_HME_WIFI_H

#include "wifi.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_log.h"

static void on_wifi_disconnect(void *arg, esp_event_base_t event_base,
                           int32_t event_id, void *event_data);

static esp_err_t wifi_sta_do_disconnect(void);

static void handler_on_sta_got_ip(void *arg, esp_event_base_t event_base,
                  int32_t event_id, void *event_data);

static void handler_on_wifi_connect(void *esp_netif, esp_event_base_t event_base,
                        int32_t event_id, void *event_data);

static esp_err_t wifi_sta_do_connect(wifi_config_t wifi_config, bool wait);

esp_err_t mk_wifi_connect(void);

esp_err_t mk_home_connect(void);

void wifi_shutdown(void);


#endif