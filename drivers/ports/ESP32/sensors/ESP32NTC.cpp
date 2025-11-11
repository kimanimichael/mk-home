//
// Created by novek on 6/25/25.
//
#include "ESP32NTC.h"

static auto TAG = "ESP32NTC";

ESP32NTC::ESP32NTC() = default;

void ESP32NTC::_init() {
    ESP_ERROR_CHECK(ntc_dev_create(&_ntc_config, &_ntc, &_adc_handle));
    ESP_ERROR_CHECK(ntc_dev_get_adc_handle(_ntc, &_adc_handle));
}

float ESP32NTC::_read() {
    if (ntc_dev_get_temperature(_ntc, &_temperature) != ESP_OK) {
        return -1.0f;
    }
    ESP_LOGI(TAG, "NTC temperature = %.2f ℃", _temperature);
    return _temperature;

}
