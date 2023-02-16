#include <iostream>
#include "MazeFloor.hpp"

MazeFloor::MazeFloor(bool visited) : MazeEntity(FLOOR_DEFAULT_SYMBOL, false), isVisited(visited) {
}

void MazeFloor::print() const {
    if (isVisited) {
        std::cout << FLOOR_VISITED_SYMBOL;
        return;
    }
    MazeEntity::print();
}

void MazeFloor::visit() {
    isVisited = true;
}

char MazeFloor::getDisplaySymbol() const {
    if (isVisited) {
        return FLOOR_VISITED_SYMBOL;
    }
    return MazeEntity::getDisplaySymbol();
}
