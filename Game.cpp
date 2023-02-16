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
            break;
        case MAIN_MENU_INPUT::RESUME_GAME:
            resume();
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
    int level;
    // open save.txt
    std::ifstream saveFile(saveFilePath);
    if (saveFile.is_open()) {
        // read current level
        saveFile >> level;
        saveFile.close();
        // get path of level save file
        std::string s = getLevelPath(level, true);
        // remove both files
        std::remove("levels/save.txt");
        std::remove(s.c_str());
    }

}

void Game::handleGameFinished(int moves) {
    // game summary
    std::cout << "Alle Level abgeschlossen" << std::endl;
    std::cout << "Anzahl benoetigte Bewegungen: ";
    std::cout << moves << std::endl;
    // clear files to avoid unintended saves.
    clearSavedFiles();
    // open main menu
    play();
}

bool Game::playLevel(Maze &maze) {
    bool levelEnded = false;
    std::cout << maze;
    // loop until player hits end or return false if user saves game
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


void Game::start(int level = 1, int movesCount = 0, Position p = {}, bool saved = false) {
    // loop while more <level>.txt exists. Loop until all levels are cleared or the game is saved.
    while (levelExists(level, saved)) {
        bool levelFinished = false;
        Maze maze = Maze::loadFromFile(getLevelPath(level, saved), movesCount, p);
        levelFinished = playLevel(maze);
        movesCount += maze.getMovesCount();
        if (levelFinished) {
            std::cout << "Level gewonnen" << std::endl;
        } else {
            return Game::save(maze, level, movesCount);
        }
        level++;
        // reset saved values before restarting the loop
        saved = false;
        p = {};
    }
    handleGameFinished(movesCount);
}

void Game::restart() {
    clearSavedFiles();
    start();
}

void Game::resume() {
    int level, movesCount, playerRow, playerCol;
    // open the save.txt and get all metadata to resume the game
    std::ifstream saveFile(saveFilePath);
    if (saveFile.is_open()) {
        saveFile >> level >> movesCount >> playerRow >> playerCol;
        saveFile.close();
        start(level, movesCount, {playerRow, playerCol}, true);
    } else {
        // is file is not open just restart
        restart();
    }
}

void Game::save(Maze &maze, int level, int movesCount) {
    // clear existing save files, to avoid unintentional files
    clearSavedFiles();
    // open save file
    std::ofstream save("levels/save.txt");
    if (save.is_open()) {
        // read values if file exists and can be opened
        save << level << " " << movesCount << " " << maze.getPlayerPositionRow() << " " << maze.getPlayerPositionCol();
        save.close();
    } else {
        // display basic error message
        std::cout << "Fortschritt konnte nicht gespeichtert werden" << std::endl;
        return;
    }
    // save the actual maze to a <level>-save.txt
    maze.saveToFile(getLevelPath(level, true));
}
