#include "cstdio"

#include "bsp.h"


#ifdef ESP32
#include "freertos/FreeRTOS.h"
extern "C" void app_main(void)
#else
int main()
#endif
{
    BSP::BSP_init();
    BSP::BSP_LED_on();
    while (1) {
        BSP::BSP_LED_on();
        vTaskDelay(500/portTICK_PERIOD_MS);
        BSP::BSP_LED_off();
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}