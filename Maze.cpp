#include "Maze.hpp"
#include<iostream>

Maze::Maze(std::vector<std::vector<MazeEntity>> &m) {
    maze = m;
}

std::ostream &operator<<(std::ostream &os, const Maze &m) {
    for (const std::vector<MazeEntity> &row: m.maze) {
        for (const MazeEntity &entity: row) {
            os << entity;
        }
        os << std::endl;
    }
};

