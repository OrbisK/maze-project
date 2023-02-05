#include <tuple>
#pragma once

enum DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player {
private:
    std::tuple<int, int> position;
    void setPositionX(int x);
    void setPositionY(int y);
public:
    Player(int x, int y);
    std::tuple<int, int> getPosition();
    int getPositionX();
    int getPositionY();
    void move(DIRECTION d);
};
