#include "Maze.hpp"
#include "MazeWall.hpp"
#include "MazeFloor.hpp"
#include<tuple>
#include <fstream>
#include <string>
#include <iostream>


Maze::Maze(std::vector<std::vector<MazeEntity *>> &e,Dimension& d, Position &start, Position &end, Position p = {}, int initialMovesCount = 0)
        : movesCount(initialMovesCount), startPos(start), endPos(end), entities(e), dimensions(d), player(p.col && p.row ? p : start) {
    if (entities[start.row][start.col]->getIsSolid() || entities[end.row][end.col]->getIsSolid()) {
        std::cout << "Start und/oder Ende darf nicht auf einem nicht betretbaren Entry liegen.";
        exit(1);
    }

    if (start.col == end.col && start.row == end.row) {
        std::cout << "Start und Ende duerfen nicht uebereinander liegen.";
        exit(1);
    }
}

Position Maze::getPlayerPosition() {
    return player.getPosition();
}

int Maze::getPlayerPositionCol() {
    return player.getPositionCol();
}

int Maze::getPlayerPositionRow() {
    return player.getPositionRow();
}

int Maze::getMovesCount() {
    return movesCount;
}

std::vector<std::vector<MazeEntity *>> Maze::getEntities() {
    return entities;
}

Player &Maze::getPlayer() {
    return player;
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
        if (!entity->getIsSolid()) {
            dynamic_cast<IVisitable*>(entity)->visit();
            movesCount++;
            player.move(direction);
        }
    } catch (std::out_of_range &) {}
    return positionIsEnd(position);
}

void printLoadFromFileError(const std::string &message, const std::string &fileName, std::exception &e) {
    std::cout << "[FEHLER] " << message << " Bitte pruefen sie die eingelesene Datei: " << fileName << std::endl;
    std::cout << e.what() << std::endl;
    exit(1);
}

void printLoadFromFileError(const std::string &message, const std::string &fileName) {
    std::cout << "[FEHLER] " << message << " Bitte pruefen sie die eingelesene Datei: " << fileName << std::endl;
    exit(1);
}

void printLoadFromFileWarning(const std::string &message, const std::string &fileName) {
    std::cout << "[Warnung] " << message << " Bitte pruefen sie die eingelesene Datei: " << fileName << std::endl;
}

Dimension parseDimensions(const std::string &row) {
    int height = std::stoi(row.substr(0, row.find(' ')));
    int width = std::stoi(row.substr(row.find(' ')));
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Dimensionen duerfen nicht kleiner als 1 sein.");
    }
    return {width, height};
}

Position parseStartPosition(const std::string &row, Dimension dimensions) {
    int startY = std::stoi(row.substr(0, row.find(' ')));
    int startX = std::stoi(row.substr(row.find(' ')));
    if (startX < 0 || startY < 0 || startY > dimensions.height ||
        startX > dimensions.width) {
        throw std::invalid_argument("Startpunkt darf nicht ausserhalb des Labyrinthes liegen.");
    }
    return {startY, startX};
}

Position parseEndPosition(const std::string &row, Dimension dimensions) {
    int endY = std::stoi(row.substr(0, row.find(' ')));
    int endX = std::stoi(row.substr(row.find(' ')));
    if (endX < 0 || endY < 0 || endY > dimensions.height || endX > dimensions.width) {
        throw std::invalid_argument("Endpunkt darf nicht ausserhalb des Labyrinthes liegen.");
    }
    return {endY, endX};
}

std::vector<MazeEntity *> parseMazeRow(const std::string &row, Dimension dimensions, const std::string &filename) {
    std::vector<MazeEntity *> rowData;
    int colIndex = 0;
    for (char entity: row) {
        if (colIndex + 1 > dimensions.width) {
            printLoadFromFileWarning(
                    "Alle Spalten des Labyrinths, die groesser als die vorgegebenen Spaltenanzahl sind werden ignoriert.",
                    filename);
            break;
        }
        switch (entity) {
            case WALL_SYMBOL:
                rowData.push_back(new MazeWall);
                break;
            case FLOOR_DEFAULT_SYMBOL:
                rowData.push_back(new MazeFloor(false));
                break;
            case FLOOR_VISITED_SYMBOL:
                rowData.push_back(new MazeFloor(true));
                break;
            default:
                printLoadFromFileError(
                        "Im Labyrinth ist ein unbekanntest Zeichen",
                        filename);
                break;
        }
        colIndex++;
    }

    while (rowData.size() < dimensions.width) {
        rowData.push_back(new MazeFloor(false));
    }
    return rowData;
}

bool Maze::saveToFile(const std::string &filename) {
    std::ofstream file(filename); // Datei öffnen

    if (file.is_open()) { // Überprüfen, ob die Datei geöffnet werden konnte
        file << dimensions.height << " " << dimensions.width << std::endl;
        file << startPos.row << " " << startPos.col << std::endl;
        file << endPos.row << " " << endPos.col << std::endl;
        int r = 0;
        for (const std::vector<MazeEntity *> &row: getEntities()) {
            int c = 0;
            for (auto entity: row) {
                file << entity->getDisplaySymbol();
                c++;
            }
            file << std::endl;
            r++;
        }
        file.close(); // Datei schließen
        std::cout << "Text wurde erfolgreich in die Datei geschrieben." << std::endl;
    } else {
        std::cout << "Datei konnte nicht geöffnet werden." << std::endl;
    }
}

Maze Maze::loadFromFile(const std::string &filename, int initialMoves = 0, Position p = {}) {
    std::ifstream file(filename);
    std::string row;
    int lineNumber = 1;
    int mazeRow = 0;
    Dimension dimensions{};
    Position startPoint{};
    Position endPoint{};

    std::vector<std::vector<MazeEntity *>> data;

    while (file) {
        if (file.eof()) {
            break;
        }
        std::getline(file, row); // read each line into a string
        switch (lineNumber) {
            case 1: {
                try {
                    dimensions = parseDimensions(row);
                } catch (std::invalid_argument &e) {
                    printLoadFromFileError("Beim Einlesen der Labyrinthdimensionen ist ein Fehler aufgetreten.",
                                           filename, e);
                }
                break;
            }
            case 2: {
                try {
                    startPoint = parseStartPosition(row, dimensions);
                } catch (std::invalid_argument &e) {
                    printLoadFromFileError("Beim Einlesen des Startpunktes ist ein Fehler aufgetreten.", filename,
                                           e);
                }
                break;
            }
            case 3: {
                try {
                    endPoint = parseEndPosition(row, dimensions);
                } catch (std::invalid_argument &e) {
                    printLoadFromFileError("Beim Einlesen des Endpunktes ist ein Fehler aufgetreten.",
                                           filename, e);
                }
                break;
            }
            default:
                int mazeRowNumber = lineNumber - 3;
                if (mazeRowNumber > dimensions.height) {
                    printLoadFromFileWarning(
                            "Alle Zeilen des Labyrinths, die groesser als die vorgegebenen Zeilenanzahl sind werden ignoriert.",
                            filename);
                    break;
                }

                data.push_back(parseMazeRow(row, dimensions, filename));
                mazeRow++;
                break;
        }
        lineNumber++;
    }

    return Maze(data, dimensions, startPoint, endPoint, p, initialMoves);
}

std::ostream &operator<<(std::ostream &os, Maze &m) {
    int r = 0;
    for (const std::vector<MazeEntity *> &row: m.getEntities()) {
        int c = 0;
        for (auto entity: row) {
            if (m.getPlayerPositionCol() == c && m.getPlayerPositionRow() == r) {
                os << 'X';
            } else if (m.startPos.col == c && m.startPos.row == r) {
                os << 'S';
            } else if (m.endPos.col == c && m.endPos.row == r) {
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

