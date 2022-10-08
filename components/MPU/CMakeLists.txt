aux_source_directory(. DIR_MPU_SRCS)

add_library(MPU ${DIR_MPU_SRCS})

include_directories(../Utils)

target_link_libraries(MPU PUBLIC hardware_spi pico_stdlib Utils Utils)