#include "led.h"
#include "bsp.h"
#include "ESP32_MCU.h"
#include "ESP32NTC.h"

#include "freertos/FreeRTOS.h"

#include <cstdint>

namespace BSP{
    void BSP_init() {
        BSP_init_actuators();
        get_ambient_ntc()->_init();
    }

    void BSP_init_actuators() {
        get_default_onboard_led()->LED_init();
    }

    void BSP_LED_on() {
        get_default_onboard_led()->LED_on();
    }

    void BSP_LED_off() {
        get_default_onboard_led()->LED_off();
    }

    void BSP_alternate_LED_on() {
        get_alternate_onboard_led()->LED_on();
    }

    void BSP_alternate_LED_off() {
        get_alternate_onboard_led()->LED_off();
    }

    void BSP_delay(unsigned int ms) {
        vTaskDelay(ms/portTICK_PERIOD_MS);
    }

    MCU* BSP_get_MCU() {
        static ESP32_MCU mcu;
        return &mcu;
    }

    NTC* get_ambient_ntc() {
        static ESP32NTC ntc;
        return &ntc;
    }


    LED* get_default_onboard_led() {
        static LED led(2);
        return &led;
    }

    LED* get_alternate_onboard_led() {
        static LED led(12);
        return &led;
    }

};
