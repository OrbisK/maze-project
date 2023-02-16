#pragma once

#include "MazeEntity.hpp"

const char WALL_SYMBOL = '*';

/**
 * MazeWall.
 *
 * An entity of a maze. A MazeWall is solid. If an entity is solid, it cannot be visited by a player.
 */
class MazeWall : public MazeEntity {
public:
    /**
     * MazeWall constructor.
     *
     * Initializes a wall as a MazeEntity with '*' as display symbol and solid.
     */
    MazeWall();
};
