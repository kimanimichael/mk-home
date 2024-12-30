cmake_minimum_required(VERSION 3.16)

if(PLATFORM STREQUAL "ESP32")
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)

    message("ESP32 port selected")
    set(CMAKE_FIND_ROOT_PATH /home/novek/.espressif/tools/xtensa-esp32-elf/esp-12.2.0_20230208/xtensa-esp32-elf)
    set(CMAKE_C_COMPILER /home/novek/.espressif/tools/xtensa-esp32-elf/esp-12.2.0_20230208/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc)
    set(CMAKE_CXX_COMPILER /home/novek/.espressif/tools/xtensa-esp32-elf/esp-12.2.0_20230208/xtensa-esp32-elf/bin/xtensa-esp32-elf-g++)
    set(CMAKE_ASM_COMPILER /home/novek/.espressif/tools/xtensa-esp32-elf/esp-12.2.0_20230208/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc)

    set(EXTRA_COMPONENT_DIRS drivers/)
    idf_build_component(drivers)

    set(EXTRA_COMPONENT_DIRS src/)
    idf_build_component(src)
    add_definitions(-DESP32)

elseif(PLATFORM STREQUAL "STM32F429ZI")
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32_toolchain.cmake)
endif()

project(mk-home)

if(PLATFORM STREQUAL "ESP32")
    add_definitions(-DESP32)
elseif(PLATFORM STREQUAL "STM32F429ZI")
    add_definitions(-DSTM32F429xx)
endif()

# Add subdirectories
#add_subdirectory(drivers)
#add_subdirectory(src)