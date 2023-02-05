cmake_minimum_required(VERSION 3.24)
project(labyrinth)

set(CMAKE_CXX_STANDARD 20)

add_executable(labyrinth main.cpp MazeEntity.hpp MazeEntity.cpp MazeWall.cpp MazeWall.hpp MazeFloor.cpp MazeFloor.hpp Maze.cpp Maze.hpp Player.cpp Player.hpp InputHandler.cpp InputHandler.hpp Game.cpp Game.hpp)
