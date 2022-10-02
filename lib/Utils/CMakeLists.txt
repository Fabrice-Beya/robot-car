aux_source_directory(. DIR_Utils_SRCS)

add_library(Utils ${DIR_Utils_SRCS})

target_link_libraries(Utils PUBLIC pico_stdlib freertos)