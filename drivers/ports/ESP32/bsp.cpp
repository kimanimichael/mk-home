#include "led.h"
#include "bsp.h"

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

    LED* get_default_onboard_led() {
        static LED led;
        return &led;
    }

};
