if (NOT DEFINED PLATFORM)
    set(PLATFORM "ESP32")
endif ()

if(PLATFORM STREQUAL "ESP32")
    idf_component_register(
            SRCS
            "main.cpp"
            REQUIRES
            drivers
    )
elseif(PLATFORM STREQUAL "stm32f429zi")
    add_executable(${PROJECT_NAME}
            main.cpp
    )
endif ()