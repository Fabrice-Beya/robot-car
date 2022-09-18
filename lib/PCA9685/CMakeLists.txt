aux_source_directory(. DIR_PCA9685_SRCS)

add_library(PCA9685 ${DIR_PCA9685_SRCS})

target_link_libraries(PCA9685 PUBLIC hardware_i2c pico_stdlib)