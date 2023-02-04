#pragma once
#include <string>

class MazeEntity {
private:
    bool isSolid;
    char displaySymbol;
public:
    bool isVisited;
    MazeEntity(char symbol, bool solid, bool visited);
    void setDisplaySymbol(char symbol);
    bool visit();
    std::string toString();
};
