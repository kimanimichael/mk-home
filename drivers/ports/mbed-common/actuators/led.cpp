#include "led.h"
#include "mbed.h"
#include "cstdio"

LED::LED(const int pin) {
    _pin = pin;
}

void LED::LED_init() {
    printf("LED init\n");
}


void LED::LED_on() {
    DigitalOut onboard_led(static_cast<PinName>(_pin));
    onboard_led.write(1);
    printf("LED on\n");
}

void LED::LED_off() {
    DigitalInOut onboard_led(static_cast<PinName>(_pin));
    onboard_led.output();
    onboard_led.write(0);
    printf("LED off\n");
}
