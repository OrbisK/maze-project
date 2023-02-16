#include "Maze.hpp"
#include "MazeWall.hpp"
#include "MazeFloor.hpp"
#include<tuple>
#include <fstream>
#include <string>
#include <iostream>


Maze::Maze(std::vector<std::vector<MazeEntity *>> &e, Dimension &d, Position &start, Position &end, Position p = {},
           int initialMovesCount = 0)
        : movesCount(initialMovesCount), startPos(start), endPos(end), entities(e), dimensions(d),
          player(p.col && p.row ? p : start) {
    // handle start or end on wall
    if (entities[start.row][start.col]->getIsSolid() || entities[end.row][end.col]->getIsSolid()) {
        std::cout << "Start und/oder Ende darf nicht auf einem nicht betretbaren Entry liegen.";
        exit(1);
    }
    // handle start and end on same entitiy
    if (start.col == end.col && start.row == end.row) {
        std::cout << "Start und Ende duerfen nicht uebereinander liegen.";
        exit(1);
    }
}

int Maze::getPlayerPositionCol() {
    return player.getPositionCol();
}

int Maze::getPlayerPositionRow() {
    return player.getPositionRow();
}

int Maze::getMovesCount() const {
    return movesCount;
}

std::vector<std::vector<MazeEntity *>> Maze::getEntities() {
    return entities;
}

MazeEntity *Maze::getMazeEntityByPosition(Position position) {
    return entities.at(position.row).at(position.col);
}

bool Maze::positionIsEnd(Position p) const {
    return p.col == endPos.col && p.row == endPos.row;
}

bool Maze::movePlayer(DIRECTION direction) {
    MazeEntity *entity;
    Position position{};
    // try to move in a certain direction
    try {
        switch (direction) {
            case DIRECTION::RIGHT:
                position = {getPlayerPositionRow(), getPlayerPositionCol() + 1};
                break;
            case DIRECTION::LEFT:
                position = {getPlayerPositionRow(), getPlayerPositionCol() - 1};
                break;
            case DIRECTION::UP:
                position = {getPlayerPositionRow() - 1, getPlayerPositionCol()};
                break;
            case DIRECTION::DOWN:
                position = {getPlayerPositionRow() + 1, getPlayerPositionCol()};
                break;
        }
        entity = getMazeEntityByPosition(position);
        // handle legal move
        if (!entity->getIsSolid()) {
            dynamic_cast<IVisitable *>(entity)->visit();
            movesCount++;
            player.move(direction);
        }
    } catch (std::out_of_range &) {
        // catch out of range, if move will end outside the maze
    }
    // return true if the player hits the end
    return positionIsEnd(position);
}

/**
 * Simple error message handler with exception.
 * @param message The custom error message.
 * @param fileName A simple stacktrace (the filename).
 * @param e the actual exception.
 */
void printLoadFromFileError(const std::string &message, const std::string &fileName, std::exception &e) {
    std::cout << "[FEHLER] " << message << " Bitte pruefen sie die eingelesene Datei: " << fileName << std::endl;
    std::cout << e.what() << std::endl;
    exit(1);
}

/**
 * Simple error message handler.
 * @param message The custom error message.
 * @param fileName A simple stacktrace (the filename).
 */
void printLoadFromFileError(const std::string &message, const std::string &fileName) {
    std::cout << "[FEHLER] " << message << " Bitte pruefen sie die eingelesene Datei: " << fileName << std::endl;
    exit(1);
}

/**
 * Simple warning message handler.
 * @param message The custom warning message.
 * @param fileName A simple stacktrace (the filename).
 */
void printLoadFromFileWarning(const std::string &message, const std::string &fileName) {
    std::cout << "[Warnung] " << message << " Bitte pruefen sie die eingelesene Datei: " << fileName << std::endl;
}

/**
 * Parse dimension from string.
 *
 * Splits dimensions into row and col.
 * Returns Dimension as struct.
 *
 * @param row The row as string.
 * @return The dimensions.
 */
Dimension parseDimensions(const std::string &row) {
    // split string into 2 parts (height, width)
    int height = std::stoi(row.substr(0, row.find(' ')));
    int width = std::stoi(row.substr(row.find(' ')));
    // simple legal check
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Dimensionen duerfen nicht kleiner als 1 sein.");
    }
    return {width, height};
}
/**
 * Parse start position from string.
 *
 * Splits the start position into row and col.
 * Returns Point as struct.
 *
 * @param row The row as string.
 * @param dimensions The current maze dimensions.
 * @return The start point.
 */
Position parseStartPosition(const std::string &row, Dimension dimensions) {
    // split string into 2 parts (row, col)
    int startY = std::stoi(row.substr(0, row.find(' ')));
    int startX = std::stoi(row.substr(row.find(' ')));
    // simple legal check
    if (startX < 0 || startY < 0 || startY >= dimensions.height ||
        startX >= dimensions.width) {
        throw std::invalid_argument("Startpunkt darf nicht ausserhalb des Labyrinthes liegen.");
    }
    return {startY, startX};
}

/**
 * Parse end position from string.
 *
 * Splits the end position into row and col.
 * Returns Point as struct.
 *
 * @param row The row as string.
 * @param dimensions The current maze dimensions.
 * @return The end point.
 */
Position parseEndPosition(const std::string &row, Dimension dimensions) {
    // split string into 2 parts (row, col)
    int endY = std::stoi(row.substr(0, row.find(' ')));
    int endX = std::stoi(row.substr(row.find(' ')));
    // simple legal check
    if (endX < 0 || endY < 0 || endY >= dimensions.height || endX >= dimensions.width) {
        throw std::invalid_argument("Endpunkt darf nicht ausserhalb des Labyrinthes liegen.");
    }
    return {endY, endX};
}

/**
 * Parse a row of MazeEntities from string.
 *
 * Splits the row into separat MazeEntities, based on the symbol.
 *
 * @param row The current row to parse.
 * @param dimensions The current maze dimensions.
 * @param filename The filename.
 * @return Vector of MazeEntities.
 */
std::vector<MazeEntity *> parseMazeRow(const std::string &row, Dimension dimensions, const std::string &filename) {
    std::vector<MazeEntity *> rowData;
    int colIndex = 0;
    // iterate all rows
    for (char entity: row) {
        //handle col > maze width to prevent unnecessary/illegal loops
        if (colIndex + 1 > dimensions.width) {
            printLoadFromFileWarning(
                    "Alle Spalten des Labyrinths, die groesser als die vorgegebenen Spaltenanzahl sind werden ignoriert.",
                    filename);
            break;
        }
        // handle different symbols
        switch (entity) {
            case WALL_SYMBOL:
                // if wall symbol initialize wall and push to rowData
                rowData.push_back(new MazeWall);
                break;
            case FLOOR_DEFAULT_SYMBOL:
                // if default floor symbol initialize floor (not visited) and push to rowData
                rowData.push_back(new MazeFloor(false));
                break;
            case FLOOR_VISITED_SYMBOL:
                // if visited floor symbol initialize floor (visited) and push to rowData
                rowData.push_back(new MazeFloor(true));
                break;
            default:
                // print error if some unknown symbols
                printLoadFromFileError(
                        "Im Labyrinth ist ein unbekanntest Zeichen",
                        filename);
                break;
        }
        colIndex++;
    }
    // if less entities than dimensions width -> fill with floors (not visited)
    while (rowData.size() < dimensions.width) {
        rowData.push_back(new MazeFloor(false));
    }
    return rowData;
}

void Maze::saveToFile(const std::string &filename) {
    // open save file
    std::ofstream file(filename);

    if (file.is_open()) {
        // write to file if possible
        // apply format
        file << dimensions.height << " " << dimensions.width << std::endl;
        file << startPos.row << " " << startPos.col << std::endl;
        file << endPos.row << " " << endPos.col << std::endl;
        int r = 0;
        // print maze rows one by one
        for (const std::vector<MazeEntity *> &row: getEntities()) {
            int c = 0;
            for (auto entity: row) {
                file << entity->getDisplaySymbol();
                c++;
            }
            file << std::endl;
            r++;
        }
        file.close();
        std::cout << "Labyrinth wurde erfolgreich gespeichert." << std::endl;
    } else {
        std::cout << "Labyrinth konnte nicht gespeichert werden" << std::endl;
    }
}

Maze Maze::loadFromFile(const std::string &filename, int initialMoves = 0, Position p = {}) {
    // open maze save file
    std::ifstream file(filename);
    // initialize defaults
    std::string row;
    int lineNumber = 1;
    int mazeRow = 0;
    Dimension dimensions{};
    Position startPoint{};
    Position endPoint{};

    std::vector<std::vector<MazeEntity *>> data;

    // loop while unread file content
    while (file) {
        // break if EOF is reached.
        if (file.eof()) {
            break;
        }
        // read each line into a string
        std::getline(file, row);
        // handle file format
        switch (lineNumber) {
            case 1: {
                // parse first row as maze dimension
                try {
                    dimensions = parseDimensions(row);
                } catch (std::invalid_argument &e) {
                    printLoadFromFileError("Beim Einlesen der Labyrinthdimensionen ist ein Fehler aufgetreten.",
                                           filename, e);
                }
                break;
            }
            case 2: {
                // parse second row as start point
                try {
                    startPoint = parseStartPosition(row, dimensions);
                } catch (std::invalid_argument &e) {
                    printLoadFromFileError("Beim Einlesen des Startpunktes ist ein Fehler aufgetreten.", filename,
                                           e);
                }
                break;
            }
            case 3: {
                // parse third row as end point
                try {
                    endPoint = parseEndPosition(row, dimensions);
                } catch (std::invalid_argument &e) {
                    printLoadFromFileError("Beim Einlesen des Endpunktes ist ein Fehler aufgetreten.",
                                           filename, e);
                }
                break;
            }
            default:
                // parse following rows as maze rows
                int mazeRowNumber = lineNumber - 3;
                // ignore all symbols if they don't fit dimensions
                if (mazeRowNumber > dimensions.height) {
                    printLoadFromFileWarning(
                            "Alle Zeilen des Labyrinths, die groesser als die vorgegebenen Zeilenanzahl sind werden ignoriert.",
                            filename);
                    break;
                }
                // parse maze row as vector of entities and push them to rowDtaa
                data.push_back(parseMazeRow(row, dimensions, filename));
                mazeRow++;
                break;
        }
        lineNumber++;
    }
    // initialize maze with data from file
    return Maze(data, dimensions, startPoint, endPoint, p, initialMoves);
}

std::ostream &operator<<(std::ostream &os, Maze &m) {
    int r = 0;
    // loop over all maze rows
    for (const std::vector<MazeEntity *> &row: m.getEntities()) {
        int c = 0;
        // loop over every entity of row and print it to terminal
        for (auto entity: row) {
            if (m.getPlayerPositionCol() == c && m.getPlayerPositionRow() == r) {
                // print player
                os << 'X';
            } else if (m.startPos.col == c && m.startPos.row == r) {
                // print start
                os << 'S';
            } else if (m.endPos.col == c && m.endPos.row == r) {
                // print end
                os << 'E';
            } else {
                entity->print();
            }
            c++;
        }
        os << std::endl;
        r++;
    }
    return os;
};

