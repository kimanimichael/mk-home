#ifndef MQTT_H
#define MQTT_H

class MQTTClient {

public:
    MQTTClient();

    ~MQTTClient();
    /**
     * @brief Initialize board specific functionalities e.g. logging
     */
    static void init();
    /**
     * @brief Start MQTT client
     */
    static void start();
    /**
     * @brief Connect MQTT client
     */
    bool connect();
    /**
     * @brief Disconnect MQTT client
     */
    bool disconnect();
    /**
     * @brief Establish internet connection
     */
    static void get_internet_connection();
    /**
     * @brief log mqtt error
     * @param message error message
     * @param error_code code specific to the implementation
     */
    static void log_error(const char *message, int error_code);
    /**
     * @brief Get default instance
     * @return Pointer to MQTTClient
     */
    static MQTTClient * get_default_instance();
    /**
     *
     * @param topic MQTT topic
     * @param message message to send
     */
    static void send_mqtt_message(const char *topic, const char *message);
};

#endif