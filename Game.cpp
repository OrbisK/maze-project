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
    std::ifstream saveFile(saveFilePath);
    if (saveFile.is_open()) {
        saveFile >> level;
        saveFile.close();
        std::string s = getLevelPath(level, true);
        std::remove("levels/save.txt");
        std::remove(s.c_str());
    }

}

void Game::handleGameFinished(int moves) {
    InputHandler::setOutputColor(OUTPUT_COLORS::GREEN);
    std::cout << "Alle Level abgeschlossen" << std::endl;
    InputHandler::setOutputColor(OUTPUT_COLORS::DEFAULT);
    std::cout << "Anzahl benoetigte Bewegungen: ";
    InputHandler::setOutputColor(OUTPUT_COLORS::YELLOW);
    std::cout << moves << std::endl;
    InputHandler::setOutputColor(OUTPUT_COLORS::DEFAULT);
    clearSavedFiles();
    play();
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


void Game::start(int level = 1, int movesCount = 0, Position p = {}, bool saved = false) {
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
    std::ifstream saveFile(saveFilePath);
    if (saveFile.is_open()) {
        saveFile >> level >> movesCount >> playerRow >> playerCol;
        saveFile.close();
        start(level, movesCount, {playerRow, playerCol}, true);
    } else {
        restart();
    }
}

void Game::save(Maze &maze, int level, int movesCount) {
    clearSavedFiles();
    std::ofstream save("levels/save.txt"); // Datei öffnen

    if (save.is_open()) { // Überprüfen, ob die Datei geöffnet werden konnte
        save << level << " " << movesCount << " " << maze.getPlayerPositionRow() << " " << maze.getPlayerPositionCol();
        save.close(); // Datei schließen
    } else {
        std::cout << "Fortschritt konnte nicht gespeichtert werden" << std::endl; // Handle error
        return;
    }
    maze.saveToFile(getLevelPath(level, true));
}
