#pragma once
#include "InputHandler.hpp"
#include "Maze.hpp"

class Game {
public:
    explicit Game();
    void start();
private:
    void clearSavedFiles();
};
