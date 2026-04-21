cmake_minimum_required(VERSION 3.16)

project(b3sh VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(b3sh src/main.cpp)

target_sources(b3sh PRIVATE
    src/utils/helper.cpp
    src/handlers/base.cpp
    src/handlers/builtin.cpp
    src/handlers/app.cpp
    src/handlers/pipe.cpp
    src/commands/cd.cpp
    src/commands/export.cpp
    src/commands/pwd.cpp
    src/terminal/input.cpp
    src/terminal/completion.cpp

)
target_include_directories(b3sh PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_compile_options(b3sh PRIVATE -Wall -Wextra -Werror -O2)