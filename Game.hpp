#pragma once
#include "InputHandler.hpp"
#include "Maze.hpp"

class Game {
public:
    /**
     * Play a Game.
     *
     * Starts "Game Engine" with main menu.
     */
    static void play();
private:
    /**
     * Clear saved files.
     *
     * Clears all save files in `/levels/` directory.
     */
    static void clearSavedFiles();
    /**
     * Start a certain level.
     *
     * Plays a level inside the `/levels/` directory until its finished or saved.
     * @param level Level to play. Default: 1
     * @param movesCount Initial moves count. Default: 0
     * @param position Initial player postion. Default {}
     * @param saved If the level is a
     */
    static void start(int level, int movesCount, Position position, bool saved);
    static void restart();
    static void resume();
    static void playCustom();
    static void save(Maze& maze, int level, int movesCount);
    static bool playLevel(Maze& maze);
    static void handleGameFinished(int moves);
};
