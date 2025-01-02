#include "led.h"
#include "driver/gpio.h"
#include "cstdio"

LED::LED(const int pin) {
    _pin = pin;
}

void LED::LED_init() {
    gpio_set_direction(static_cast<gpio_num_t>(_pin), GPIO_MODE_OUTPUT);
    printf("LED init\n");
}


void LED::LED_on() {
    gpio_set_level(static_cast<gpio_num_t>(_pin), 1);
    printf("LED on\n");
}

void LED::LED_off() {
    gpio_set_level(static_cast<gpio_num_t>(_pin), 0);
    printf("LED off\n");
}
