cmake_minimum_required(VERSION 3.20)
project(task8)

set(CMAKE_CXX_STANDARD 20)

add_executable(task8 game.cpp terminal_base.cpp terminal.cpp terminal_base.h terminal.h gameLibrary.cpp gameLibrary.h)
