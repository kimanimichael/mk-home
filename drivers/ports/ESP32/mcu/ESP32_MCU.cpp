#include "ESP32_MCU.h"
#include "esp_log.h"

static auto TAG = "mk-home-mcu";

ESP32_MCU::ESP32_MCU() = default;

const char* ESP32_MCU::get_mcu_id() {
    _err = esp_efuse_mac_get_default(_mac_address);
    if (_err != ESP_OK) {
        printf("Error getting MAC address\n");
    }

    sniprintf(_device_id, sizeof(_device_id), "%02X%02X%02X-%02X%02X%02X", _mac_address[0], _mac_address[1], _mac_address[2], _mac_address[3], _mac_address[4], _mac_address[5]);
    ESP_LOGI(TAG, "Chip UID = %s", _device_id);
    return _device_id;
}
