#include "led.h"
#include "driver/gpio.h"
#include "cstdio"

void LED::LED_init() {
    gpio_set_direction(gpio_num_t::GPIO_NUM_2, GPIO_MODE_OUTPUT);
    printf("LED init\n");
}


void LED::LED_on() {
    gpio_set_level(gpio_num_t::GPIO_NUM_2, 1);
    printf("LED on\n");
}

void LED::LED_off() {
    gpio_set_level(gpio_num_t::GPIO_NUM_2, 0);
    printf("LED off\n");
}
