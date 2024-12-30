cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

if (NOT DEFINED PLATFORM)
    set(PLATFORM "ESP32")
endif ()

if(PLATFORM STREQUAL "ESP32")
    idf_component_register(
            SRCS
            "ports/ESP32/actuators/led.cpp"
            "ports/ESP32/bsp.cpp"
            INCLUDE_DIRS
            "./include"
            "./include/actuators"
            REQUIRES
            "driver"
    )
else()
    message(FATAL_ERROR "Platform not supported: ${PLATFORM}")

endif ()