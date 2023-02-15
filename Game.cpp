#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdio>
#include <string>
#include "Game.hpp"
#include "InputHandler.hpp"


void Game::play() {
    MAIN_MENU_INPUT mainMenu = InputHandler::getMainMenuInput();

    switch (mainMenu) {
        case MAIN_MENU_INPUT::START_GAME:
            restart();
//            TODO: spiel Starten
            break;
        case MAIN_MENU_INPUT::RESUME_GAME:
            // TODO: Spiel fortsetzen!
            break;
        case MAIN_MENU_INPUT::CUSTOM_GAME:
            // TODO: Eigenes Level starten
            break;
        case MAIN_MENU_INPUT::EXIT:
            std::cout << "Spiel wurde beendet" << std::endl;
            exit(0);
        default:
            exit(1);
    }
}

std::string getLevelPath(int level, bool saved) {
    return "levels/" + std::to_string(level) + (saved ? "-saved.txt" : ".txt");
}

bool levelExists(int level, bool saved) {
    return std::filesystem::exists(getLevelPath(level, saved));
}

const std::string saveFilePath = "levels/save.txt";


void Game::clearSavedFiles() {
    int level, moves;
    std::ifstream saveFile(saveFilePath);
    if (saveFile.is_open()) {
        saveFile >> level >> moves;
        saveFile.close();
        std::string s = getLevelPath(level, true);
        std::remove("levels/save.txt");
        std::remove(s.c_str());
    }

}

bool Game::playLevel(Maze &maze) {
    bool levelEnded = false;
    std::cout << maze;
    while (!levelEnded) {
        GAME_INPUT choice = InputHandler::getGameInput();
        switch (choice) {
            case GAME_INPUT::PLAYER_MOVE_RIGHT:
                levelEnded = maze.movePlayer(DIRECTION::RIGHT);
                break;
            case GAME_INPUT::PLAYER_MOVE_LEFT:
                levelEnded = maze.movePlayer(DIRECTION::LEFT);
                break;
            case GAME_INPUT::PLAYER_MOVE_UP:
                levelEnded = maze.movePlayer(DIRECTION::UP);
                break;
            case GAME_INPUT::PLAYER_MOVE_DOWN:
                levelEnded = maze.movePlayer(DIRECTION::DOWN);
                break;
            case GAME_INPUT::SAVE_GAME:
            default:
                return false;
        }
        std::cout << maze;
    }
    return true;
}

void Game::restart() {
    clearSavedFiles();
    int level = 1;
    int movesCount = 0;
    bool levelFinished = false;
    while (levelExists(level, false)) {
        Maze maze = Maze::loadFromFile(getLevelPath(level, false), movesCount);
        levelFinished = playLevel(maze);
        movesCount += maze.getMovesCount();
        if(levelFinished){
            std::cout << "Level gewonnen" << std::endl;
        }else{
            return Game::save(maze, level, movesCount);
        }
        level++;
    }
}

void Game::save(Maze& maze, int level, int movesCount) {
    std::cout << movesCount;
    // save moves count. save last unfinished level
}
