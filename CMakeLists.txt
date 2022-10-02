# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Include pico sdk build functions
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set the name of the project and c/c++ standards
project(main C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(lib/Utils)
add_subdirectory(lib/freertos)
add_subdirectory(lib/PCA9685)
# add_subdirectory(lib/MPU6050)
add_subdirectory(lib/MPU)
add_subdirectory(lib/Car)

include_directories(./lib/Utils)
include_directories(./lib/freertos)
include_directories(./lib/PCA9685)
# include_directories(./lib/MPU6050)
include_directories(./lib/MPU)
include_directories(./lib/Car)

add_executable(main 
    main.c
)

# enable usb output, disable uart output
pico_enable_stdio_usb(main 0)
pico_enable_stdio_uart(main 1)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(main)

target_link_libraries(main Utils PCA9685 Car MPU  freertos)