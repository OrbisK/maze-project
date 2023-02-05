#pragma once
#include "InputHandler.hpp"
#include "Maze.hpp"

class Game {
public:
    Game(Maze &maze);
private:
    Maze maze;
};
