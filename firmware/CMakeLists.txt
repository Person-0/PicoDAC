# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.3.0)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.3.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(PicoDAC C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

if (TARGET tinyusb_device)

    add_executable(PicoDAC
        PicoDAC.c
        src/usb_descriptors.c
        src/dac.c
        src/neopixel.c
    )

    pico_generate_pio_header(${PROJECT_NAME}
        ${CMAKE_CURRENT_LIST_DIR}/pios/neopixel.pio
    )

    target_include_directories(PicoDAC PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
    )

    target_link_libraries(PicoDAC
        pico_stdlib
        hardware_i2c
        hardware_pio
        tinyusb_device
    )

    pico_add_extra_outputs(PicoDAC)

elseif(PICO_ON_DEVICE)
    message("Skipping PicoDAC because TinyUSB submodule is not initialized in the SDK")
endif()
