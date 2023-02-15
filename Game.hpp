#pragma once
#include "InputHandler.hpp"
#include "Maze.hpp"

class Game {
public:
    static void play();
private:
    static void clearSavedFiles();
    static void restart();
    static void save();
    static void playLevel(Maze& maze);
};
