#include "led.h"
#include "bsp.h"
#include "freertos/FreeRTOS.h"

#include <cstdint>

namespace BSP{
    void BSP_init() {
        BSP_init_actuators();
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


    LED* get_default_onboard_led() {
        static LED led(2);
        return &led;
    }

    LED* get_alternate_onboard_led() {
        static LED led(12);
        return &led;
    }

};
