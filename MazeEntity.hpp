#pragma once
#include <string>

class MazeEntity {
private:
    bool isSolid;
    char displaySymbol;
public:
    MazeEntity(char symbol, bool solid);
};
