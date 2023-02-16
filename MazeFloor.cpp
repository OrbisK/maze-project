#include <iostream>
#include "MazeFloor.hpp"

MazeFloor::MazeFloor(bool visited) : MazeEntity(FLOOR_DEFAULT_SYMBOL, false), isVisited(visited) {
}

void MazeFloor::print() const {
    std::cout << getDisplaySymbol();
}

void MazeFloor::visit() {
    isVisited = true;
}

char MazeFloor::getDisplaySymbol() const {
    // if floor is visited return '.' as symbol
    if (isVisited) {
        return FLOOR_VISITED_SYMBOL;
    }
    return MazeEntity::getDisplaySymbol();
}
