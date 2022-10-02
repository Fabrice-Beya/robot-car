aux_source_directory(. DIR_MPU6050_SRCS)

add_library(MPU6050 ${DIR_MPU6050_SRCS})

target_link_libraries(MPU6050 PUBLIC hardware_i2c pico_stdlib Utils)