#include "MazeEntity.hpp"
#include <iostream>

void MazeEntity::setDisplaySymbol(char symbol) {
    displaySymbol = symbol;
}

bool MazeEntity::getIsSolid() const {
    return isSolid;
}

char MazeEntity::getDisplaySymbol() const {
    return displaySymbol;
}

MazeEntity::MazeEntity(char symbol, bool solid) : displaySymbol(symbol), isSolid(solid) {
}

void MazeEntity::print() const{
    std::cout << displaySymbol;
}


MazeEntity::~MazeEntity() = default;
