#include "mqtt.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp32_wifi.h"
#include "mqtt_client.h"

static const char *TAG = "mk-home-mqtt";

void MQTTClient::init() {
    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("mqtt_client", ESP_LOG_VERBOSE);
    esp_log_level_set("mqtt_example", ESP_LOG_VERBOSE);
    esp_log_level_set("transport_base", ESP_LOG_VERBOSE);
    esp_log_level_set("esp-tls", ESP_LOG_VERBOSE);
    esp_log_level_set("transport", ESP_LOG_VERBOSE);
    esp_log_level_set("outbox", ESP_LOG_VERBOSE);

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
}

void connect_wifi() {
    mk_home_connect();
}

void MQTTClient::get_internet_connection() {
    connect_wifi();
}


void MQTTClient::log_error(const char* message, const int error_code) {
    if (error_code !=0 ) {
        ESP_LOGE(TAG, "MQTT error %s: 0x%x", message, error_code);
    }
}

esp_mqtt_client_handle_t client;

void MQTTClient::start() {
    constexpr esp_mqtt_client_config_t mqtt_cfg = {
        .broker = {
            .address = {
                .uri = "mqtt://mqtt.eclipseprojects.io"
            },
        },
    };

    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);
}

void MQTTClient::send_mqtt_message(const char* topic, const char* message) {
    int msg_id = esp_mqtt_client_publish(client, topic, message, 0, 1, 0);
    ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
}


