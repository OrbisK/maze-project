#pragma once

#include <string>

/**
 * Possible user inputs if the user is playing a maze.
 */
enum GAME_INPUT {
    PLAYER_MOVE_UP,
    PLAYER_MOVE_DOWN,
    PLAYER_MOVE_LEFT,
    PLAYER_MOVE_RIGHT,

    SAVE_GAME,
    UNVALID_GAME_INPUT,
};

/**
 * Possible user inputs if the user is in the main menu.
 */
enum MAIN_MENU_INPUT {
    START_GAME,
    RESUME_GAME,
    CUSTOM_GAME,
    EXIT,

    UNVALID_MAIN_MENU_INPUT
};

/**
 * Allowed colors for the console.
 */
enum OUTPUT_COLORS {
    GREEN,
    YELLOW,
    RED,
    DEFAULT
};

/**
 * Organizes the user inputs.
 *
 * Handles user input in current state of the game.
 */
class InputHandler {

private:
    /**
     * Returns the action to be performed when the user plays a maze.
     *
     * Processes user input and assigns it to executable actions that can be performed within a game.
     *
     * @param input The character of the user input.
     * @return The GAME_INPUT which can be performed.
     */
    static GAME_INPUT getGameInputByUserInput(char input);

    /**
     * Returns the action to be performed when the user is in the main menu.
     *
     * Processes user input and assigns it to executable actions that can be performed within the main menu.
     *
     * @param input The character of the user input.
     * @return The MAIN_MENU_INPUT which can be performed.
     */
    static MAIN_MENU_INPUT getMainMenuInputByUserInput(char input);

public:
    /**
     * Prompts the user to enter a game action.
     *
     * Prompts the user to enter a valid action that can be performed within a game.
     * Prompts the user until a valid input is made.
     *
     * @return The GAME_INPUT which can be performed.
     */
    static GAME_INPUT getGameInput();

    /**
     * Prompts the user to enter a main menu action.
     *
     * Prompts the user to enter a valid action that can be performed within the main menu.
     * Prompts the user until a valid input is made.
     *
     * @return The MAIN_MENU_INPUT which can be performed.
     */
    static MAIN_MENU_INPUT getMainMenuInput();

    /**
     * Changes the color of terminal output.
     *
     * Changes the color of the following terminal output if the terminal supports it.
     * Will be applied to all following output.
     * To reset, pass OUTPUT_COLORS::DEFAULT.
     *
     * @param color The new terminal color.
     */
    static void setOutputColor(OUTPUT_COLORS color);
};
