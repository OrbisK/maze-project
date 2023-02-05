#pragma once

#include <string>

enum GAME_INPUT {
    PLAYER_MOVE_UP,
    PLAYER_MOVE_DOWN,
    PLAYER_MOVE_LEFT,
    PLAYER_MOVE_RIGHT,

    SAVE_GAME,
    UNVALID_INPUT,
};

class InputHandler {

private:
    static GAME_INPUT getGameInputByUserInput(char input);
public:
    InputHandler();
    static GAME_INPUT getGameInput();
};
