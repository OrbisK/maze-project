#include "Game.hpp"
#include "InputHandler.hpp"

Game::Game(Maze &m) : maze(m) {
    InputHandler::getGameInput();
}