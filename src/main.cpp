#include "bsp.h"
#include "mqtt.h"
#include "http.h"


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

    HTTPClient::get_default_http_instance()->_init();

    while (1) {

        BSP::BSP_LED_on();
        MQTTClient::send_mqtt_message("/MK_HOME_NAKUJA", "{\"ev\":\"sensors\",\"temp\":25, \"brightness\":500, \"pressure\":98 }\n");
        HTTPClient::get_default_http_instance()->_post("{\"ev\":\"sensors\",\"temp\":25, \"brightness\":500, \"pressure\":98 }\n");

        BSP::BSP_delay(10000);

        BSP::BSP_LED_off();
        MQTTClient::send_mqtt_message("/MK_HOME_NAKUJA", "{\"ev\":\"devices\",\"fridge\":ON, \"microwave\":OFF, \"NAKUJA_MK\":ON }\n");
        HTTPClient::get_default_http_instance()->_post("{\"ev\":\"sensors\",\"temp\":25, \"brightness\":500, \"pressure\":98 }\n");

        BSP::BSP_delay(10000);
    }
}
