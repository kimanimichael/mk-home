#include "ESP32_http.h"
#include "bsp.h"

#include <cstring>
#include <sys/param.h>
#include <cstdlib>
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_tls.h"
#include "esp_mac.h"
#if CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
#include "esp_crt_bundle.h"
#endif

#include "esp32_wifi.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define MAX_HTTP_RECV_BUFFER 512
#define MAX_HTTP_OUTPUT_BUFFER 2048

static auto TAG = "mk-home-http";

uint8_t dev_id[6];

ESP32HttpClient::ESP32HttpClient() {

}

void ESP32HttpClient::_init() {
    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("http_client", ESP_LOG_VERBOSE);
    esp_log_level_set("http_example", ESP_LOG_VERBOSE);
    esp_log_level_set("transport_base", ESP_LOG_VERBOSE);
    esp_log_level_set("esp-tls", ESP_LOG_VERBOSE);
    esp_log_level_set("transport", ESP_LOG_VERBOSE);
    esp_log_level_set("outbox", ESP_LOG_VERBOSE);

    snprintf(_url, sizeof(_url),
             "https://michael.alwaysdata.net/mk/message/%s",
             BSP::BSP_get_MCU()->get_mcu_id());
    ESP_LOGI(TAG, "Full URL: %s", _url);

    _config.url = _url;
    _config.cert_pem = root_ca_pem;
    _client = esp_http_client_init(&_config);
}

void ESP32HttpClient::_post(const char *message) {
    esp_http_client_set_method(_client, HTTP_METHOD_POST);
    esp_http_client_set_header(_client, "Content-Type", "application/json");
    esp_http_client_set_post_field(_client, message, strlen(message));

    _err = esp_http_client_perform(_client);

    if (_err == ESP_OK) {
        ESP_LOGI(TAG, "HTTP POST Status = %d, content_length = %"PRId64, esp_http_client_get_status_code(_client), esp_http_client_get_content_length(_client));
    } else {
        ESP_LOGE(TAG, "HTTP POST request failed: %s", esp_err_to_name(_err));
    }

}

void ESP32HttpClient::_close() {

}

void ESP32HttpClient::_log_error(const char* message, int error_code) {

}

esp_err_t ESP32HttpClient::_http_event_handler(esp_http_client_event_t* evt) {
return ESP_OK;
}


void ESP32HttpClient::_get_internet_connection() {
    mk_home_connect();
}

HTTPClient* HTTPClient::get_default_http_instance() {
    static ESP32HttpClient http_client;
    return &http_client;
}
