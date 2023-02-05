#include "MazeEntity.hpp"
#include "Player.hpp"
#include<vector>
#include <tuple>

#pragma once

class Maze {
private:
    std::vector<std::vector<MazeEntity>> maze;
    Player player;
public:
    Maze(Maze &m);
    Maze(std::vector<std::vector<MazeEntity>> &maze, std::tuple<int, int> &playerPosition);
    friend std::ostream &operator<<(std::ostream &os, Maze &m);
    std::vector<std::vector<MazeEntity>> getMaze();
    Player& getPlayer();
    int getPlayerPositionX();
    int getPlayerPositionY();
};
