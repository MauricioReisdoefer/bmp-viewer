cmake_minimum_required(VERSION 3.16)

project(BMPViewer C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)

include_directories(include)

file(GLOB SRC_FILES src/*.c)

add_executable(bmp_viewer ${SRC_FILES})

target_link_libraries(bmp_viewer PRIVATE SDL3::SDL3)

# cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/libs/SDL3"