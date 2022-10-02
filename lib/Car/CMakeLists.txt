aux_source_directory(. DIR_Car_SRCS)

include_directories(../PCA9685)
include_directories(../Utils)

add_library(Car ${DIR_Car_SRCS})

target_link_libraries(Car PUBLIC PCA9685 pico_stdlib freertos Utils)