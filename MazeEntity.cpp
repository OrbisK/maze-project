#include "MazeEntity.hpp"

void MazeEntity::setDisplaySymbol(char symbol) {
    displaySymbol = symbol;
}

void MazeEntity::setIsVisited(bool visit) {
    isVisited = visit;
}

bool MazeEntity::getIsSolid() {
    return isSolid;
}

bool MazeEntity::getIsVisited() {
    return isVisited;
}


MazeEntity::MazeEntity(char symbol, bool solid, bool visited) {
    displaySymbol = symbol;
    isSolid = solid;
    isVisited = visited;
}

std::ostream &operator<<(std::ostream &os, const MazeEntity &e) {
    std::string s;
    return os << s + e.displaySymbol;
}