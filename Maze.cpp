#include "Maze.hpp"
#include<iostream>
#include<tuple>

char PLAYER_SYMBOL = 'X';

Maze::Maze(std::vector<std::vector<MazeEntity>> &m, std::tuple<int, int> player) {
    maze = m;
    playerPosition = player;
}

int Maze::getPlayerPositionX() {
    return std::get<0>(playerPosition);
}

int Maze::getPlayerPositionY() {
    return std::get<1>(playerPosition);
}

std::vector<std::vector<MazeEntity>> Maze::getMaze() {
    return maze;
}

std::ostream &operator<<(std::ostream &os, Maze &m) {
    int r = 0;
    for (const std::vector<MazeEntity> &row: m.getMaze()) {
        int c = 0;
        for (const MazeEntity &entity: row) {
            if(m.getPlayerPositionX() == c && m.getPlayerPositionY() == r){
                os << "X";
            }else{
                os << entity;
            }
            c++;
        }
        os << std::endl;
        r++;
    }
};

