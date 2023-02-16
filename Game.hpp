#pragma once
#include "InputHandler.hpp"
#include "Maze.hpp"

class Game {
public:
    static void play();
private:
    static void clearSavedFiles();
    static void start(int level, int movesCount, Position position, bool saved);
    static void restart();
    static void resume();
    static void save(Maze& maze, int level, int movesCount);
    static bool playLevel(Maze& maze);
    static void handleGameFinished(int moves);
};
