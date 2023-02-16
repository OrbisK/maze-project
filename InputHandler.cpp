#include "InputHandler.hpp"
#include <iostream>
#include <vector>
#include <cstdio>
#include <limits>

GAME_INPUT InputHandler::getGameInputByUserInput(char input) {
    switch (input) {
        case 'O':
        case 'o':
        case '8':
            return GAME_INPUT::PLAYER_MOVE_UP;
        case 'U':
        case 'u':
        case '2':
            return GAME_INPUT::PLAYER_MOVE_DOWN;
        case 'L':
        case 'l':
        case '4':
            return GAME_INPUT::PLAYER_MOVE_LEFT;
        case 'R':
        case 'r':
        case '6':
            return GAME_INPUT::PLAYER_MOVE_RIGHT;
        case 'S':
        case 's':
            return GAME_INPUT::SAVE_GAME;
        default:
            return GAME_INPUT::UNVALID_GAME_INPUT;
    }
}

char getCharFromInput() {
    char c = std::getchar();
    // removes previous input if existing
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return c;
}

GAME_INPUT InputHandler::getGameInput() {
    GAME_INPUT input = GAME_INPUT::UNVALID_GAME_INPUT;
    // loops until input is valid
    while (input == GAME_INPUT::UNVALID_GAME_INPUT) {
        std::cout << "Was moechten Sie machen?" << std::endl;
        std::cout << "Sie sind das X und muessen zum E" << std::endl;
        std::cout << "Bewegung:" << std::endl;
        std::cout << "[O|8]: Oben [U|2]: Unten [L|4]: Links [R|6]: Rechts [S]: Speichern" << std::endl;
        input = getGameInputByUserInput(getCharFromInput());
    }
    return input;
}

MAIN_MENU_INPUT InputHandler::getMainMenuInputByUserInput(char input) {
    // map char to action
    switch (input) {
        case 's':
        case 'S':
            return MAIN_MENU_INPUT::START_GAME;
        case 'f':
        case 'F':
            return MAIN_MENU_INPUT::RESUME_GAME;
        case 'v':
        case 'V':
            return MAIN_MENU_INPUT::EXIT;
        default:
            return MAIN_MENU_INPUT::UNVALID_MAIN_MENU_INPUT;
    }
}

MAIN_MENU_INPUT InputHandler::getMainMenuInput() {
    MAIN_MENU_INPUT input = MAIN_MENU_INPUT::UNVALID_MAIN_MENU_INPUT;
    // loop until input is valid
    while (input == MAIN_MENU_INPUT::UNVALID_MAIN_MENU_INPUT) {
        std::cout << "Hauptmenue" << std::endl;
        std::cout << "Auswahl:" << std::endl;
        std::cout << "[S]: neues Spiel starten [F]: Spiel fortsetzen [V]: Verlassen" << std::endl;
        input = getMainMenuInputByUserInput(getCharFromInput());
    }
    return input;
}
