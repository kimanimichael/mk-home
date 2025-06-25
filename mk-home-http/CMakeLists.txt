cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

if (PLATFORM STREQUAL "mbed-os")
    add_library(http INTERFACE)

    if (PORT STREQUAL "STM32F429ZI")
        target_include_directories(http INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR}/ports/STM32F429ZI/mbed/include)
    endif ()

    target_include_directories(http INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/include/
    )
    target_sources(http INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/ports/mbed-common/http.cpp
    )
else ()
    idf_component_register(
            SRCS
            "ports/ESP32/ESP32_http.cpp"
            INCLUDE_DIRS
            "./include"
            "ports/ESP32"
            REQUIRES
            "driver"
            drivers
            "nvs_flash"
            "esp_netif"
            "esp_event"
            "esp_http_client"
            "esp-tls"
            "esp_hw_support"
            "wifi"
    )
endif ()