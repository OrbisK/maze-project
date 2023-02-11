#include <tuple>
#pragma once

enum DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Position {
    int row;
    int col;
};

class Player {
private:
    Position position;
    void setPositionCol(int x);
    void setPositionRow(int y);
public:
    Player(int x, int y);
    Position getPosition();
    int getPositionCol();
    int getPositionRow();
    void move(DIRECTION d);
};
