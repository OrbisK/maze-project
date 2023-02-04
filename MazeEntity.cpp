#include "MazeEntity.hpp"

void MazeEntity::setDisplaySymbol(char symbol) {
    displaySymbol = symbol;
}

bool MazeEntity::visit() {
    if(isSolid) {
        return false;
    }
    isVisited = true;
    return true;
}

std::string MazeEntity::toString(){
    return std::string(1, displaySymbol);;
}

MazeEntity::MazeEntity(char symbol, bool solid, bool visited ) {
    displaySymbol = symbol;
    isSolid = solid;
    isVisited = visited;
}