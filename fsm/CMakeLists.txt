cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

if (PLATFORM STREQUAL "mbed-os")
    add_library(fsm INTERFACE)

    if (PORT STREQUAL "STM32F429ZI")

    endif ()

    target_include_directories(drivers INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/include/
    )
    target_sources(drivers INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/ports/mbed-common/fsm.cpp
    )
else ()
    idf_component_register(
            SRCS
            "ports/ESP32/fsm.cpp"
            INCLUDE_DIRS
            "./include"
            REQUIRES
            "driver"
    )
endif ()

