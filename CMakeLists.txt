cmake_minimum_required(VERSION 2.6)
project(JAYBEEENGINE)

add_library(
	oluxEngine
	src/oluxEngine/core.cpp
	src/oluxEngine/core.h
)

add_executable(
	game
	src/game/main.cpp
	src/game/TestScene.cpp
	src/game/TestScene.h
)

target_link_libraries(game oluxEngine)