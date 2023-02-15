#include "Player.hpp"

Player::Player(int col, int row): position({row, col}) {}

Position Player::getPosition() {
    return position;
}
void Player::setPositionCol(int x) {
    position.col = x;
}

void Player::setPositionRow(int y) {
    position.row = y;
}

int Player::getPositionCol() {
    return position.col;
}

int Player::getPositionRow() {
    return position.row;
}

void Player::move(DIRECTION d){
    switch(d){
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
