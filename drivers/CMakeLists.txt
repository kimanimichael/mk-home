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
    )
    target_sources(drivers INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/ports/mbed-common/actuators/led.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ports/mbed-common/bsp.cpp
    )
else ()
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
endif ()

