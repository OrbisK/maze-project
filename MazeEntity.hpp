#pragma once

#include <string>

class IVisitable {
public:
    virtual void visit() = 0;
};

class MazeEntity {
private:
    bool isSolid;
    char displaySymbol;
public:
    bool getIsSolid() const;
    void setDisplaySymbol(char symbol);
    virtual char getDisplaySymbol() const;

    virtual void print() const;
    MazeEntity(char symbol, bool solid);
    virtual  ~MazeEntity();
};
