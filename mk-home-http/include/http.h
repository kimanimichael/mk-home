#ifndef _HTTP_H
#define _HTTP_H

class HTTPClient {
public:
    virtual ~HTTPClient() = default;

    /**
     * @brief Initialize client and board specific functionalities e.g. logging
     */
    virtual void _init() = 0;
    /**
     * @brief Close HTTP client
     */
    virtual void _close() = 0;
    /**
     * @brief Establish internet connection
     */
    virtual void _get_internet_connection() = 0;
    /**
     * @brief log http error
     * @param message error message
     * @param error_code code specific to the implementation
     */
    virtual  void _log_error(const char *message, int error_code) = 0;
    /**
     * @brief Send message
     * @param message http post request body
     */
    virtual void  _post(const char *message) = 0;

    /**
     * @brief Get default instance
     * @return Pointer to HTTPClient
     */
    static HTTPClient *get_default_http_instance();
};


#endif
