#pragma once

#include <string>

class MazeEntity {
private:
    bool isSolid;
    bool isVisited;
    char displaySymbol;
public:
    bool getIsSolid() const;

    bool getIsVisited() const;

    void setDisplaySymbol(char symbol);

    void setIsVisited(bool visit);

    friend std::ostream &operator<<(std::ostream &os, const MazeEntity &e);
    friend std::ostream &operator<<(std::ostream &os, const MazeEntity* e);

    MazeEntity(char symbol, bool solid, bool visited);
    virtual  ~MazeEntity();
};
