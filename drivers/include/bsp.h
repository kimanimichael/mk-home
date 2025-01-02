#ifndef __BSP_H__
#define __BSP_H__
#include "led.h"

namespace BSP
{
    void BSP_init();

    void BSP_init_actuators();

    void BSP_LED_on();

    void BSP_LED_off();

    void BSP_alternate_LED_on();

    void BSP_alternate_LED_off();

    /**
     * @brief blocking wait in line
     * @param ms no. of milliseconds to wait
     */
    void BSP_delay(unsigned int ms);

    LED* get_default_onboard_led();

    LED* get_alternate_onboard_led();
};

#endif