cmake_minimum_required(VERSION 3.16)

project(b3sh VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(b3sh src/main.cpp)

target_sources(b3sh PRIVATE
    src/utils/helper.cpp
    src/handler.cpp
)
target_include_directories(b3sh PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_compile_options(b3sh PRIVATE -Wall -Wextra -Werror -O2)