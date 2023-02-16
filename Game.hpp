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
     * Clears all save files in /levels/ directory.
     */
    static void clearSavedFiles();

    /**
     * Start a certain level.
     *
     * Plays the passed level inside the /levels/ directory until its finished or saved.
     * Handles saved moves and player position.
     *
     * @param level Level to play. Default: 1
     * @param movesCount Initial moves count. Default: 0
     * @param position Initial player postion. Default: {}
     * @param saved If the level is a saved level. Default: false
     */
    static void start(int level, int movesCount, Position position, bool saved);

    /**
     * Restart a game.
     *
     * Clears all saved files and starts a game via Game::start()
     *
     * @see Game::start()
     */
    static void restart();

    /**
     * Resumes the saved game if possible.
     *
     * Resumes the saved game. If it's not possible the game is restarted.
     *
     * @see Game::restart()
     */
    static void resume();

    /**
     * Save the current maze.
     *
     * Creates the save.txt with current moves, the current level and the player position.
     * Creates the <level>-saved.txt with the current state of the maze.
     *
     * @param maze
     * @param level
     * @param movesCount
     */
    static void save(Maze &maze, int level, int movesCount);

    /**
     * Plays the maze.
     *
     * Plays the maze with user input. Until the Player reaches the end position.
     *
     * @param maze The maze to play.
     */
    static bool playLevel(Maze &maze);

    /**
     * Handles the end of the game.
     *
     * Prints a summary of the moves and clears the saved files.
     *
     * @param moves The final count of the moves.
     */
    static void handleGameFinished(int moves);
};
