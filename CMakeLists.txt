cmake_minimum_required(VERSION 3.15)
project(cinder C)

SET(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(cinder 
    src/server.c
    src/platform/posix.c
    src/http.c
    src/log.c
)

target_include_directories(cinder PUBLIC include)

add_executable(minimal examples/minimal.c)
target_link_libraries(minimal cinder)