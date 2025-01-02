#ifndef __ACTUATORS_LED_H
#define __ACTUATORS_LED_H

class LED {
public:
    LED(int pin);

    void LED_init(void);

    void LED_on(void);

    void LED_off(void);

private:
    int _pin;
};

#endif