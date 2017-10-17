cmake_minimum_required(VERSION 3.5)
project(Robot)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c11")

set(SOURCE_FILES
    Main.c Mag.c Magnetic.c printf_t.c server.c client.c)

add_executable(Robot ${SOURCE_FILES})