#include "bsp.h"
#include "mqtt.h"


#ifdef ESP32
extern "C" void app_main(void)
#else
int main()
#endif
{
    BSP::BSP_init();
    BSP::BSP_LED_on();

    MQTTClient::init();
    MQTTClient::get_internet_connection();
    MQTTClient::start();
    while (1) {
        BSP::BSP_LED_on();
        MQTTClient::send_mqtt_message("/topic/qos0", "Temp: 25 deg Celsius\n");
        BSP::BSP_delay(200);
        BSP::BSP_LED_off();
        MQTTClient::send_mqtt_message("/topic/qos0", "Brightness: 500 nits\n");
        BSP::BSP_delay(200);
    }
}