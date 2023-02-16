#pragma once
#include <string>

enum GAME_INPUT {
    PLAYER_MOVE_UP,
    PLAYER_MOVE_DOWN,
    PLAYER_MOVE_LEFT,
    PLAYER_MOVE_RIGHT,

    SAVE_GAME,
    UNVALID_GAME_INPUT,
};

enum MAIN_MENU_INPUT{
    START_GAME,
    RESUME_GAME,
    CUSTOM_GAME,
    EXIT,

    UNVALID_MAIN_MENU_INPUT
};

enum OUTPUT_COLORS {
    GREEN,
    YELLOW,
    RED,
    DEFAULT
};

class InputHandler {

private:
    static GAME_INPUT getGameInputByUserInput(char input);
    static MAIN_MENU_INPUT getMainMenuInputByUserInput(char input);
public:
    static GAME_INPUT getGameInput();
    static MAIN_MENU_INPUT getMainMenuInput();
    static void setOutputColor(OUTPUT_COLORS color);
};
