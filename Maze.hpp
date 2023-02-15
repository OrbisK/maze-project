#include "MazeEntity.hpp"
#include "Player.hpp"
#include<vector>
#include <tuple>
#pragma once

struct Dimension {
    int width;
    int height;
};

class Maze {
private:
    std::vector<std::vector<MazeEntity *>> entities;
    Player player;
    Position startPos;
    Position endPos;
public:
    Maze(std::vector<std::vector<MazeEntity *>> &maze, Position &s, Position &e);
    friend std::ostream &operator<<(std::ostream &os, Maze &m);
    std::vector<std::vector<MazeEntity *>> getEntities();
    Player& getPlayer();
    int getPlayerPositionCol();
    int getPlayerPositionRow();
//    void saveToFile(const std::string& filename);
    static Maze loadFromFile(const std::string& filename);
};
