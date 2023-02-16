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
    Dimension dimensions;

    bool positionIsEnd(Position p) const;

    int movesCount;
public:
    Maze(std::vector<std::vector<MazeEntity *>> &maze, Dimension &d, Position &s, Position &e, Position p,
         int initialMovesCount);

    friend std::ostream &operator<<(std::ostream &os, Maze &m);

    std::vector<std::vector<MazeEntity *>> getEntities();

    Player &getPlayer();

    Position getPlayerPosition();

    int getPlayerPositionCol();

    int getPlayerPositionRow();

    int getMovesCount();

    bool saveToFile(const std::string &filename);

    static Maze loadFromFile(const std::string &filename, int initialMovesCount, Position p);

    bool movePlayer(DIRECTION direction);

    MazeEntity *getMazeEntityByPosition(Position position);
};
