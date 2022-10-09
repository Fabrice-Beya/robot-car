aux_source_directory(. DIR_Utils_SRCS)

add_library(Utils ${DIR_Utils_SRCS})

include_directories(.)

target_link_libraries(Utils PUBLIC main pico_stdlib FreeRTOS-Kernel FreeRTOS-Kernel-Heap4)