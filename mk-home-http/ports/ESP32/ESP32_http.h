//
// Created by novek on 6/16/25.
//

#ifndef ESP32_HTTP_H
#define ESP32_HTTP_H

#define MAX_HTTP_OUTPUT_BUFFER 2048

#include "http.h"
#include "esp_http_client.h"
#include "root_ca.h"


class ESP32HttpClient: public HTTPClient {
public:
    ESP32HttpClient();

    void _init() override;

    void _close() override;

    void _get_internet_connection() override;

    void _log_error(const char *message, int error_code) override;

    void _post(const char *message) override;
private:
    static esp_err_t _http_event_handler(esp_http_client_event_t *evt);

    esp_http_client_config_t _config = {
        .url = {},
        .auth_type = HTTP_AUTH_TYPE_NONE,
        .transport_type = HTTP_TRANSPORT_OVER_SSL,
    };
    esp_http_client_handle_t _client = {};

    esp_err_t _err = {};

    char _url[256] = {};

    char _response_buffer[MAX_HTTP_OUTPUT_BUFFER] = {0};

};

#endif //ESP32_HTTP_H
