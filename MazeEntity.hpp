#pragma once

#include <string>

/**
 * IVisitable Interface.
 *
 * Represents all visitable instances.
 */
class IVisitable {
public:
    /**
     * Visit function.
     */
    virtual void visit() = 0;

    /**
     * Whether the instance is solid or not.
     */
    bool isSolid = false;
};

/**
 * MazeEntity.
 *
 * An entity of a maze. A MazeEntity can be solid or not solid. If an entity is solid, it cannot be visited by a player.
 */
class MazeEntity {
private:
    /**
     * If an entity is solid, it cannot be visited by a player.
     */
    bool isSolid;
    /**
     * The symbol to use when the entity is printed.
     */
    char displaySymbol;
public:
    /**
     * MazeEntity constructor.
     *
     * Initializes a entity with the display symbol and weather it's solid or not.
     *
     * @param symbol The symbol used to represent the entity.
     * @param solid Weather it's solid or not
     */
    MazeEntity(char symbol, bool solid);
    /**
     * Getter of isSolid.
     *
     * Returns weather an entity is solid or not.
     *
     * @return Weather an entity is solid or not.
     */
    bool getIsSolid() const;

    /**
     * Getter of displaySymbol.
     *
     * Returns the displayed symbol to represent the entity as character.
     *
     * @return The symbol to display.
     */
    virtual char getDisplaySymbol() const;

    /**
     * Print the entity.
     *
     * Prints the entity to the terminal.
     */
    virtual void print() const;

    /**
     * Destructor of MazeEntity.
     *
     * Destroys the instance.
     */
    virtual  ~MazeEntity();
};
