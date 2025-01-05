cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

if (PLATFORM STREQUAL "mbed-os")
    add_library(mqtt INTERFACE)

    if (PORT STREQUAL "STM32F429ZI")
        target_include_directories(mqtt INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR}/ports/STM32F429ZI/mbed/include)
    endif ()

    target_include_directories(mqtt INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/include/
    )
    target_sources(mqtt INTERFACE
    )
else ()
    idf_component_register(
            SRCS
            "ports/ESP32/mqtt.cpp"
            INCLUDE_DIRS
            "./include"
            REQUIRES
            "driver"
            "nvs_flash"
            "esp_netif"
            "esp_event"
            "mqtt"
            "wifi"
    )
endif ()