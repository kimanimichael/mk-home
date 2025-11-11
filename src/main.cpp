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
    char message[128] = {};

    while (1) {
        float temp = BSP::get_ambient_ntc()->_read();

        snprintf(message, sizeof(message), "{\"ev\":\"sensors\",\"temp\":%.2f, \"brightness\":500, \"pressure\":98 }\n", temp);

        BSP::BSP_LED_on();
        MQTTClient::send_mqtt_message("/MK_HOME_NAKUJA", "{\"ev\":\"sensors\",\"temp\":25, \"brightness\":500, \"pressure\":98 }\n");
        HTTPClient::get_default_http_instance()->_post(message);

        BSP::BSP_delay(5000);

        BSP::BSP_LED_off();
        MQTTClient::send_mqtt_message("/MK_HOME_NAKUJA", "{\"ev\":\"devices\",\"fridge\":ON, \"microwave\":OFF, \"NAKUJA_MK\":ON }\n");
        HTTPClient::get_default_http_instance()->_post(message);

        BSP::BSP_delay(5000);
    }
}
