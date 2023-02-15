#pragma once
#include "InputHandler.hpp"
#include "Maze.hpp"

class Game {
public:
    static void play();
private:
    static void clearSavedFiles();
    static void restart();
    static void save(Maze& maze, int level, int movesCount);
    static bool playLevel(Maze& maze);
};
