cmake_minimum_required(VERSION 3.22.1)

project("xdl")

add_library(xdl STATIC
        xdl.c
        xdl_iterate.c
        xdl_linker.c
        xdl_lzma.c
        xdl_util.c
)

target_include_directories(xdl PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(xdl PRIVATE
        -Os
        -ffunction-sections
        -fdata-sections
        -fvisibility=hidden
        -flto
        -w
        -Wno-everything
        -DNDEBUG
)

target_link_libraries(xdl
        log
)
