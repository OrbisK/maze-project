#include "Player.hpp"

Player::Player(Position p) : position(p) {}

Position Player::getPosition()  {
    return position;
}

int Player::getPositionCol() const {
    return position.col;
}

int Player::getPositionRow() const {
    return position.row;
}

void Player::move(DIRECTION d) {
    switch (d) {
        case DIRECTION::UP:
            position.row -= 1;
            break;
        case DIRECTION::DOWN:
            position.row += 1;
            break;
        case DIRECTION::LEFT:
            position.col -= 1;
            break;
        case DIRECTION::RIGHT:
            position.col += 1;
            break;
    }
}
