#pragma once

#include <string>

class MazeEntity {
private:
    bool isSolid;
    char displaySymbol;
public:
    bool getIsSolid() const;
    void setDisplaySymbol(char symbol);
    char getDisplaySymbol() const;

    virtual void print() const;
    MazeEntity(char symbol, bool solid);
    virtual  ~MazeEntity();
};
