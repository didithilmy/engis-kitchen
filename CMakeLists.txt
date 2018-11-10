cmake_minimum_required(VERSION 3.6)   # CMake version check
project(engis_kitchen)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard

set(SOURCE_FILES main.c game_display.c game.c adt/imp/mesin_kar.c adt/imp/mesin_kata.c)            # Add main.cpp file of project root directory as source file
add_executable(engis_kitchen ${SOURCE_FILES})       # Add executable target with source files listed in SOURCE_FILES variable

target_link_libraries(${PROJECT_NAME} ncurses)