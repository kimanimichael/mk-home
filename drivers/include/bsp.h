#ifndef __BSP_H__
#define __BSP_H__
#include "led.h"

namespace BSP
{
    void BSP_init();

    void BSP_init_actuators();

    void BSP_LED_on();

    void BSP_LED_off();

    LED* get_default_onboard_led();
}

#endif