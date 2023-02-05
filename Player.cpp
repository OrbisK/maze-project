#include "Player.hpp"

Player::Player(int x, int y) {
    position = std::make_tuple(x, y);
}

std::tuple<int, int> Player::getPosition() {
    return position;
}
void Player::setPositionX(int x) {
    std::get<0>(position) = x;
}

void Player::setPositionY(int y) {
    std::get<1>(position) = y;
}

int Player::getPositionX() {
    return std::get<0>(position);
}

int Player::getPositionY() {
    return std::get<1>(position);
}

void Player::move(DIRECTION d){
    switch(d){
        case DIRECTION::UP:
            setPositionY(getPositionY()-1);
        case DIRECTION::DOWN:
            setPositionY(getPositionY()+1);
        case DIRECTION::LEFT:
            setPositionX(getPositionX()-1);
        case DIRECTION::RIGHT:
            setPositionX(getPositionX()+1);
    }
}

