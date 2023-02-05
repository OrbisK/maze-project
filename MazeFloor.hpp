#include "MazeEntity.hpp"

#pragma once


enum FLOOR_TPYE {
    DEFAULT,
    START,
    END
};

class MazeFloor : public MazeEntity {
private:
    FLOOR_TPYE type;

    void updateSymbol();

public:
    MazeFloor(FLOOR_TPYE type, bool isVisited);

    bool visit();

};
