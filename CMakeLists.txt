cmake_minimum_required(VERSION 3.22.1)
project("IL2CPP_Resolver")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(il2cpp_resolver SHARED
    xdl/xdl.c
    xdl/xdl_iterate.c
    xdl/xdl_linker.c
    xdl/xdl_lzma.c
    xdl/xdl_util.c
    main.cpp
)

target_include_directories(il2cpp_resolver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/xdl/include
)

target_compile_options(il2cpp_resolver PRIVATE
    -Os
    -ffunction-sections
    -fdata-sections
    -fvisibility=hidden
    -flto
    -w
    -Wno-everything
    -DNDEBUG
)

target_link_libraries(il2cpp_resolver
    log
)
