#include "bsp.h"


#ifdef ESP32
extern "C" void app_main(void)
#else
int main()
#endif
{
    BSP::BSP_init();
    BSP::BSP_LED_on();
    while (1) {
        BSP::BSP_LED_on();
        BSP::BSP_delay(200);
        BSP::BSP_LED_off();
        BSP::BSP_delay(200);
    }
}