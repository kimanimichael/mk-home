cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

if(PORT STREQUAL "ESP32")
    if (PLATFORM STREQUAL "ESP_IDF")
        include($ENV{IDF_PATH}/tools/cmake/project.cmake)

        message("ESP32 port selected with ESP_IDF")
        set(CMAKE_FIND_ROOT_PATH /home/novek/.espressif/tools/xtensa-esp32-elf/esp-12.2.0_20230208/xtensa-esp32-elf)
        set(CMAKE_C_COMPILER /home/novek/.espressif/tools/xtensa-esp32-elf/esp-12.2.0_20230208/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc)
        set(CMAKE_CXX_COMPILER /home/novek/.espressif/tools/xtensa-esp32-elf/esp-12.2.0_20230208/xtensa-esp32-elf/bin/xtensa-esp32-elf-g++)
        set(CMAKE_ASM_COMPILER /home/novek/.espressif/tools/xtensa-esp32-elf/esp-12.2.0_20230208/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc)

        set(EXTRA_COMPONENT_DIRS src/)
        idf_build_component(src)

        set(EXTRA_COMPONENT_DIRS drivers/)
        idf_build_component(drivers)

        add_definitions(-DESP32)
    else ()
        message(FATAL_ERROR "Platform not currently supported: " ${PLATFORM})
    endif ()
    project(mk-home)


elseif(PORT STREQUAL "STM32F429ZI")
    if (PLATFORM STREQUAL "mbed-os")
        message("STM32F429ZI port selected with mbed-os")

        set(APP_TARGET mk-home)


        set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/mbed-os CACHE INTERNAL "")
        set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR}/mbed CACHE INTERNAL "")

        SET(CMAKE_COLOR_MAKEFILE ON)
        add_compile_options(-fdiagnostics-color=always)

        include(${MBED_PATH}/tools/cmake/app.cmake)
        project(${APP_TARGET})

        add_subdirectory(${MBED_PATH})
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/drivers)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

        add_executable(${APP_TARGET})
        mbed_configure_app_target(${APP_TARGET})

        target_link_libraries(${APP_TARGET}
            PRIVATE
                mbed-os
                drivers
                src
        )
        mbed_set_post_build(${APP_TARGET})

        option(VERBOSE_BUILD "Have a verbose build process")
        if(VERBOSE_BUILD)
            set(CMAKE_VERBOSE_MAKEFILE ON)
        endif()
    else ()
        message(FATAL_ERROR "Platform not currently supported for STM32F429ZI: " ${PLATFORM})
    endif ()

else ()
    message(FATAL_ERROR "Port not currently supported: " ${PORT})
endif()


# Add subdirectories
#add_subdirectory(drivers)
#add_subdirectory(src)