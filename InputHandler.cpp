#include "InputHandler.hpp"
#include<iostream>
#include <vector>

InputHandler::InputHandler() = default;

GAME_INPUT InputHandler::getGameInputByUserInput(char input) {
    switch(input){
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
            return GAME_INPUT::UNVALID_INPUT;
    }
}


GAME_INPUT InputHandler::getGameInput() {
    GAME_INPUT input = GAME_INPUT::UNVALID_INPUT;
    while(input == GAME_INPUT::UNVALID_INPUT){
        std::cout << "Was moechten Sie machen?" << std::endl;
        std::cout << "Bewegung:" << std::endl;
        std::cout << "[O|8]: Oben [U|2]: Unten [L|4]: Links [R|6]: Rechts" << std::endl;
        std::string choice;
        std::cin >> choice;
        input = getGameInputByUserInput(choice[0]);
    }
    return input;
}