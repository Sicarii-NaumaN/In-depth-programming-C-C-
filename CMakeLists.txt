cmake_minimum_required(VERSION 3.16)
project(task1)

set(CMAKE_C_STANDARD 11)
add_compile_options(-Werror -Wall -Wextra -I )
set(SOURCE project/src/main.c project/src/utils.c )
include_directories(project/include)
add_executable(task ${SOURCE})

