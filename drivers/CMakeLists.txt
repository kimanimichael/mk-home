cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

if (PLATFORM STREQUAL "mbed-os")
    add_library(drivers INTERFACE)

    if (PORT STREQUAL "STM32F429ZI")
        target_include_directories(drivers INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR}/ports/STM32F429ZI/mbed/include)
    endif ()

    target_include_directories(drivers INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/include/
            ${CMAKE_CURRENT_SOURCE_DIR}/include/actuators
            ${CMAKE_CURRENT_SOURCE_DIR}/include/sensors/
            ${CMAKE_CURRENT_SOURCE_DIR}/include/mcu/
    )
    target_sources(drivers INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/ports/mbed-common/actuators/led.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ports/mbed-common/bsp.cpp
    )
else ()
    idf_component_register(
            SRCS
            "ports/ESP32/actuators/led.cpp"
            "ports/ESP32/mcu/ESP32_MCU.cpp"
            "ports/ESP32/bsp.cpp"
            "ports/ESP32/sensors/ESP32NTC.cpp"
            INCLUDE_DIRS
            "./include"
            "./include/actuators"
            "./include/sensors"
            "./include/mcu"
            "ports/ESP32/mcu/"
            "ports/ESP32/sensors/"
            REQUIRES
            "driver"
            "ntc_driver"
    )
endif ()

