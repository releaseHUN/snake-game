cmake_minimum_required(VERSION 3.0)
project(snake_game C)

set(CMAKE_C_STANDARD 11)

add_executable(snake_game main.c econio.c drawing.c map.c gameLogic.c)