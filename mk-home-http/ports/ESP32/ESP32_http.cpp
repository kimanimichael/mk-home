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
    _config.event_handler = _http_event_handler;
    _config.user_data = _response_buffer;
    _client = esp_http_client_init(&_config);
}

void ESP32HttpClient::_post(const char *message) {
    esp_http_client_set_method(_client, HTTP_METHOD_POST);
    esp_http_client_set_header(_client, "Content-Type", "application/json");
    esp_http_client_set_post_field(_client, message, strlen(message));

    _err = esp_http_client_perform(_client);

    if (_err == ESP_OK) {
        ESP_LOGI(TAG, "HTTP POST Status = %d, content_length = %"PRId64, esp_http_client_get_status_code(_client), esp_http_client_get_content_length(_client));
        ESP_LOGI(TAG, "HTTP POST response:%s\n", _response_buffer);
    } else {
        ESP_LOGE(TAG, "HTTP POST request failed: %s", esp_err_to_name(_err));
    }

    if (_err != ESP_OK) {
        ESP_LOGE(TAG, "HTTP POST cleanup failed: %s", esp_err_to_name(_err));
    }
}

void ESP32HttpClient::_close() {

}

void ESP32HttpClient::_log_error(const char* message, int error_code) {

}

esp_err_t ESP32HttpClient::_http_event_handler(esp_http_client_event_t* evt) {
    static char *output_buffer;  // Buffer to store the response of http request from event handler
    static int output_len;       // Stores number of bytes read
    esp_err_t err;
    int mbedtls_err;

    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            // Clean the buffer in case of a new request
            if (output_len == 0 && evt->user_data) {
                // we are just starting to copy the output data into the use
                memset(evt->user_data, 0, MAX_HTTP_OUTPUT_BUFFER);
            }
            /*
             *  Check for chunked encoding is added as the URL for chunked encoding used in this example returns binary data.
             *  However, event handler can also be used in case chunked encoding is used.
             */
            if (!esp_http_client_is_chunked_response(evt->client)) {
                // If user_data buffer is configured, copy the response into the buffer
                int copy_len = 0;
                if (evt->user_data) {
                    // The last byte in evt->user_data is kept for the NULL character in case of out-of-bound access.
                    copy_len = MIN(evt->data_len, (MAX_HTTP_OUTPUT_BUFFER - output_len));
                    if (copy_len) {
                        memcpy(evt->user_data + output_len, evt->data, copy_len);
                    }
                } else {
                    int content_len = esp_http_client_get_content_length(evt->client);
                    if (output_buffer == NULL) {
                        // We initialize output_buffer with 0 because it is used by strlen() and similar functions therefore should be null terminated.
                        output_buffer = (char *) calloc(content_len + 1, sizeof(char));
                        output_len = 0;
                        if (output_buffer == NULL) {
                            ESP_LOGE(TAG, "Failed to allocate memory for output buffer");
                            return ESP_FAIL;
                        }
                    }
                    copy_len = MIN(evt->data_len, (content_len - output_len));
                    if (copy_len) {
                        memcpy(output_buffer + output_len, evt->data, copy_len);
                    }
                }
                output_len += copy_len;
            }

            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
            if (output_buffer != NULL) {
                // Response is accumulated in output_buffer. Uncomment the below line to print the accumulated response
                // ESP_LOG_BUFFER_HEX(TAG, output_buffer, output_len);
                free(output_buffer);
                output_buffer = NULL;
            }
            output_len = 0;
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            mbedtls_err = 0;
            err = esp_tls_get_and_clear_last_error((esp_tls_error_handle_t)evt->data, &mbedtls_err, NULL);
            if (err != 0) {
                ESP_LOGI(TAG, "Last esp error code: 0x%x", err);
                ESP_LOGI(TAG, "Last mbedtls failure: 0x%x", mbedtls_err);
            }
            if (output_buffer != NULL) {
                free(output_buffer);
                output_buffer = NULL;
            }
            output_len = 0;
            break;
        case HTTP_EVENT_REDIRECT:
            ESP_LOGD(TAG, "HTTP_EVENT_REDIRECT");
            esp_http_client_set_header(evt->client, "From", "user@example.com");
            esp_http_client_set_header(evt->client, "Accept", "text/html");
            esp_http_client_set_redirection(evt->client);
            break;
    }
    return ESP_OK;
}


void ESP32HttpClient::_get_internet_connection() {
    mk_home_connect();
}

HTTPClient* HTTPClient::get_default_http_instance() {
    static ESP32HttpClient http_client;
    return &http_client;
}
