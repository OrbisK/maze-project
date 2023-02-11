#include <iostream>
#include "MazeFloor.hpp"

MazeFloor::MazeFloor(bool visited) : MazeEntity(FLOOR_DEFAULT_SYMBOL, false), isVisited(visited) {
}

bool MazeFloor::getIsVisited() const {
    return isVisited;
}

void MazeFloor::print() const {
    if(isVisited){
        std::cout <<FLOOR_VISITED_SYMBOL;
        return;
    }
    MazeEntity::print();
}

