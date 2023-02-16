#include "MazeEntity.hpp"
#include "Player.hpp"
#include<vector>
#include <tuple>

#pragma once

/**
 * Simple structure to handle the maze dimension.
 */
struct Dimension {
    int width;
    int height;
};

/**
 * The maze.
 *
 * The actual maze with all its entities.
 * A maze has a start,an end, a player position and dimensions.
 */
class Maze {
private:
    /**
     * 2D Vector of all maze entites.
     *
     * 2D Vector (row, column) of all MazeEntities (Walls and Floors).
     */
    std::vector<std::vector<MazeEntity *>> entities;
    /**
     * The Player.
     */
    Player player;
    /**
     * The position of the start.
     */
    Position startPos;
    /**
     * The position of the end.
     */
    Position endPos;
    /**
     * The maze dimensions.
     */
    Dimension dimensions;
    /**
     * The current number of all moves the player has made.
     */
    int movesCount;


    /**
     * Is the passed position the end position?
     *
     * Returns whether the position is the end of the maze.
     * The labyrinth is completed when the player is at the end position.
     *
     * @param p The position to compare with the end.
     * @return Is the passed position the end?
     */
    bool positionIsEnd(Position p) const;

public:
    /**
     * Maze constructor.
     *
     * Initializes a maze with all passed enitities, the dimension, the start position, the end position,
     * the current player position and the initial number of moves.
     *
     * @param entities 2D vector of all maze entities.
     * @param dimension The dimensions of the maze.
     * @param start The start position.
     * @param end The end position.
     * @param player The initial player position.
     * @param moves The current number of all moves.
     */
    Maze(std::vector<std::vector<MazeEntity *>> &entities, Dimension &dimension, Position &start, Position &end,
         Position player,
         int moves);

    /**
     * Overloading operator.
     *
     * Used to print the maze on the terminal.
     *
     * @param os The OS stream.
     * @param maze The maze.
     * @return The OS stream.
     */
    friend std::ostream &operator<<(std::ostream &os, Maze &maze);

    /**
     * Getter of entities.
     *
     * Returns 2D vector of maze entities.
     * @return 2D vector of entities
     */
    std::vector<std::vector<MazeEntity *>> getEntities();

    /**
     * Getter for the player column.
     *
     * Returns the current column of the player.
     *
     * @return Player column.
     */
    int getPlayerPositionCol();

    /**
     * Getter for the player column.
     *
     * Returns the current column of the player.
     *
     * @return Player column.
     */
    int getPlayerPositionRow();

    /**
     * Getter of current number of moves.
     *
     * Returns the number of moves made by the player.
     *
     * @return Number of moves.
     */
    int getMovesCount() const;

    /**
     * Save the maze to a file.
     *
     * Saves the maze instance to a file. The file name can be passed as a parameter.
     * The dimensions, the start position, the end position and the maze elements are written to the file.
     * The visited floors will be written as '.'.
     *
     * @param filename The path where the file should be saved.
     */
    void saveToFile(const std::string &filename);

    /**
     * Return a maze from a given file.
     *
     * Returns a maze instance written to the passed path.
     * Processes the file format with the first line as maze dimensions, the second line as start position,
     * the third as end position and the following as maze entities.
     *
     * @param filename The file name to initialize the maze from.
     * @param initialMovesCount The current number of moves. Default: 0
     * @param player The initial position of the player. Default: start position
     * @return The initialized maze instance.
     */
    static Maze loadFromFile(const std::string &filename, int initialMovesCount, Position player);

    /**
     * Moves the player into the passed direction.
     *
     * Moves the player in the specified direction, if possible. Returns true when the player reaches the end.
     *
     * @param direction The direction to move.
     * @return If the player has reached the end.
     */
    bool movePlayer(DIRECTION direction);

    /**
     * Get a maze entity by given position.
     * @param position The position to get the entity.
     * @return The entity at the gives position.
     * @throws std::out_of_range If the position is not within the dimensions of the maze.
     */
    MazeEntity *getMazeEntityByPosition(Position position);
};
