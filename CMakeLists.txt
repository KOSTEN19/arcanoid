cmake_minimum_required(VERSION 3.0)
project(arcanoid LANGUAGES C)
add_executable(${PROJECT_NAME} arcanoid.h drawing.c game_logic.c main.c drawing.h)
install(TARGETS ${PROJECT_NAME})