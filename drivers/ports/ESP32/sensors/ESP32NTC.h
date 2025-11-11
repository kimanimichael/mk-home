    //
// Created by novek on 6/25/25.
//

#ifndef ESP32NTC_H
#define ESP32NTC_H

#include "ntc.h"
#include "ntc_driver.h"

class ESP32NTC: public NTC {
public:
    ESP32NTC();

    void _init() override;

    float _read() override;

private:
    ntc_config_t _ntc_config = {
        .circuit_mode = CIRCUIT_MODE_NTC_VCC,
        .unit = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_12,
        .channel = ADC_CHANNEL_4,
        .b_value = 3950,
        .r25_ohm = 10000,
        .fixed_ohm = 10000,
        .vdd_mv = 3300,
    };
    ntc_device_handle_t _ntc = nullptr;
    adc_oneshot_unit_handle_t _adc_handle = nullptr;

};

#endif //ESP32NTC_H
