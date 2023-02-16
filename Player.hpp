#include <tuple>

#pragma once

/**
 * Directions a player can move.
 */
enum DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

/**
 * Basic structure to represent a position.
 */
struct Position {
    int row;
    int col;
};

/**
 * Player.
 *
 * Player represents the current position of the maze player. A player can move in a certain direction.
 */
class Player {
private:
    /**
     * The players position.
     */
    Position position;

public:
    /**
     * Constructor of Player.
     *
     * Initializes a player instance at a certain position.
     *
     * @param pos The initial position of the player.
     */
    explicit Player(Position pos);

    /**
     * Getter for position.
     *
     * @return The position.
     */
    Position getPosition();

    /**
     * Getter for the positions column.
     *
     * @return The positions column
     */
    int getPositionCol() const;

    /**
     * Getter for the positions row.
     *
     * @return The positions row
     */
    int getPositionRow() const;

    /**
     * Move the player.
     *
     * Move the player in a direction.
     *
     * @param direction The direction to move into.
     */
    void move(DIRECTION direction);
};
