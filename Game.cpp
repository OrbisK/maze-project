#include <iostream>
#include <filesystem>
#include <cstdio>
#include <string>
#include "Game.hpp"
#include "InputHandler.hpp"

Game::Game() = default;

void Game::start() {
    MAIN_MENU_INPUT mainMenu = InputHandler::getMainMenuInput();

    switch(mainMenu){
        case MAIN_MENU_INPUT::START_GAME:
            clearSavedFiles();
//            TODO: spiel Starten
            break;
        case MAIN_MENU_INPUT::RESUME_GAME:
            // TODO: Spiel fortsetzen!
            break;
        case MAIN_MENU_INPUT::EXIT:
            std::cout << "Spiel wurde beendet" << std::endl;
            exit(0);
        default:
            exit(1);
    }
}

void Game::clearSavedFiles() {
    int level = 1;
    while(std::filesystem::exists("levels/"+std::to_string(level)+"-saved.txt")){
        std::string s = "levels/" + std::to_string(level)+"-saved.txt";
        std::remove(s.c_str());
        level++;
    }
}
