cmake_minimum_required(VERSION 3.23)
project(build_a_lisp C)

set(CMAKE_C_STANDARD 17)

# Readline dir
set(READLINE_DIR /usr/include/readline)

# Readline include
include_directories(${READLINE_DIR})


add_executable(build_a_lisp main.c)

target_link_libraries(build_a_lisp readline)






