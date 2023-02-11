#include "MazeEntity.hpp"
#pragma once

const char FLOOR_DEFAULT_SYMBOL = ' ';
const char FLOOR_VISITED_SYMBOL = '.';


class MazeFloor : public MazeEntity {
private:
public:
    explicit MazeFloor(bool isVisited);
    bool visit();

};
