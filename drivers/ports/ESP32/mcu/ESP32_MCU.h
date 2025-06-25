#ifndef ESP32_DEVICE_ID_H
#define ESP32_DEVICE_ID_H

#include "mcu.h"
#include "esp_mac.h"

class ESP32_MCU : public MCU {
public:
    ESP32_MCU();

    const char* get_mcu_id() override;

private:
    uint8_t _mac_address[6] = {};
    esp_err_t _err = {};
};

#endif
