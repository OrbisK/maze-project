#include "MazeEntity.hpp"

#pragma once

const char FLOOR_DEFAULT_SYMBOL = ' ';
const char FLOOR_VISITED_SYMBOL = '.';

/**
 * MazeFloor.
 *
 * An entity of a maze. A MazeFloor is not solid. If an entity is solid, it cannot be visited by a player.
 */
class MazeFloor : public MazeEntity, public IVisitable {
private:
    /**
     * Weather the floor is visited or not.
     */
    bool isVisited;
public:
    /**
     * MazeFloor constructor.
     *
     * Initializes a floor as a MazeEntity with ' ' as display symbol and not solid.
     * You can pass isVisited to set the default isVisited state of the floor.
     *
     * @param isVisited Weather the floor has already been visited or not.
     */
    explicit MazeFloor(bool isVisited);

    /**
     * Print the floor instance.
     *
     * Prints the instance to the terminal.
     * '.': Floor is visited.
     * ' ': Floor is not visited.
     */
    void print() const override;

    /**
     * Getter of symbol to display.
     *
     * Returns:
     * '.': Floor is visited.
     * ' ': Floor is not visited.
     *
     * @return the display symbol
     */
    char getDisplaySymbol() const override;

    /**
     * Visit Function.
     *
     * Sets isVisited to true.
     */
    void visit() override;
};
