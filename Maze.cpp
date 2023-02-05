#include "Maze.hpp"
#include<iostream>
#include<tuple>

Maze::Maze(std::vector<std::vector<MazeEntity>> &m, std::tuple<int, int> &playerPosition): player(std::get<0>(playerPosition), std::get<1>(playerPosition)) {
    maze = m;
}

Maze::Maze(Maze &m) = default;

int Maze::getPlayerPositionX() {
    return player.getPositionX();
}

int Maze::getPlayerPositionY() {
    return player.getPositionY();
}

std::vector<std::vector<MazeEntity>> Maze::getMaze() {
    return maze;
}

Player& Maze::getPlayer() {
    return player;
}

std::ostream &operator<<(std::ostream &os, Maze &m) {
    int r = 0;
    for (const std::vector<MazeEntity> &row: m.getMaze()) {
        int c = 0;
        for (const MazeEntity &entity: row) {
            if (m.getPlayerPositionX() == c && m.getPlayerPositionY() == r) {
                os << "X";
            } else {
                os << entity;
            }
            c++;
        }
        os << std::endl;
        r++;
    }
    return os;
};

