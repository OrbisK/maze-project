#include "Maze.hpp"
#include "MazeWall.hpp"
#include "MazeFloor.hpp"
#include<tuple>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

Maze::Maze(std::vector<std::vector<MazeEntity *>> &e, Position &start, Position &end) : player(
        start.col, start.row), startPos(start), endPos(end), entities(e) {
    if(entities[start.row][start.col]->getIsSolid() || entities[end.row][end.col]->getIsSolid()){
        std::cout << "Start und/oder Ende darf nicht auf einem nicht betretbaren Entry liegen.";
        exit(1);
    }

    if(start.col == end.col && start.row == end.row){
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

std::vector<std::vector<MazeEntity *>> Maze::getEntities() {
    return entities;
}

Player &Maze::getPlayer() {
    return player;
}

std::ostream &operator<<(std::ostream &os, Maze &m) {
    int r = 0;
    for (std::vector<MazeEntity *> row: m.getEntities()) {
        int c = 0;
        for (auto entity: row) {
            if (m.getPlayerPositionCol() == c && m.getPlayerPositionRow() == r) {
                os << "X";
            }else if(m.startPos.col == c && m.startPos.row == r){
                os << "S";
            }else if(m.endPos.col == c && m.endPos.row == r){
                os << "E";
            }
            else {
                os << entity;
            }
            c++;
        }
        os << std::endl;
        r++;
    }
    return os;
};

void printLoadFromFileError(const std::string& message, const std::string& fileName, std::exception &e) {
    std::cout << "[FEHLER] " << message << " Bitte pruefen sie die eingelesene Datei: " << fileName << std::endl;
    std::cout << e.what() << std::endl;
    exit(1);
}

void printLoadFromFileError(const std::string& message, const std::string& fileName) {
    std::cout << "[FEHLER] " << message << " Bitte pruefen sie die eingelesene Datei: " << fileName << std::endl;
    exit(1);
}

void printLoadFromFileWarning(const std::string& message, const std::string& fileName) {
    std::cout << "[Warnung] " << message << " Bitte pruefen sie die eingelesene Datei: " << fileName << std::endl;
}


Maze Maze::loadFromFile(const std::string &fileName) {

    std::ifstream file(fileName);
    std::string row;
    int lineNumber = 1;
    int mazeRow = 0;
    Dimension dimensions{};
    Position startPoint{};
    Position endPoint{};

    std::vector<std::vector<MazeEntity *>> data;

    while (file) {
        if(file.eof()){
            break;
        }
        std::getline(file, row); // read each line into a string
        switch (lineNumber) {
            case 1: {
                try {
                    int height = std::stoi(row.substr(0, row.find(' ')));
                    int width = std::stoi(row.substr(row.find(' ')));
                    if (width <= 0 || height <= 0) {
                        throw std::invalid_argument("Dimensionen duerfen nicht kleiner als 1 sein.");
                    }
                    dimensions.height = height;
                    dimensions.width = width;
                } catch (std::invalid_argument &e) {
                    printLoadFromFileError("Beim Einlesen der Labyrinthdimensionen ist ein Fehler aufgetreten.",
                                           fileName, e);
                }
                break;
            }
            case 2: {
                try {
                    int startY = std::stoi(row.substr(0, row.find(' ')));
                    int startX = std::stoi(row.substr(row.find(' ')));
                    if (startX < 0 || startY < 0 || startY > dimensions.height ||
                        startX > dimensions.width) {
                        throw std::invalid_argument("Startpunkt darf nicht ausserhalb des Labyrinthes liegen.");
                    }
                    startPoint.row = startY;
                    startPoint.col = startX;
                } catch (std::invalid_argument &e) {
                    printLoadFromFileError("Beim Einlesen des Startpunktes ist ein Fehler aufgetreten.", fileName, e);
                }
                break;
            }
            case 3: {
                try {
                    int endY = std::stoi(row.substr(0, row.find(' ')));
                    int endX = std::stoi(row.substr(row.find(' ')));
                    if (endX < 0 || endY < 0 || endY > dimensions.height || endX > dimensions.width) {
                        throw std::invalid_argument("Endpunkt darf nicht ausserhalb des Labyrinthes liegen.");
                    }
                    endPoint.row = endY;
                    endPoint.col = endX;
                } catch (std::invalid_argument &e) {
                    printLoadFromFileError("Beim Einlesen des Endpunktes ist ein Fehler aufgetreten.",
                                           fileName, e);
                }
                break;
            }
            default:
                std::vector<MazeEntity *> rowData;
                int mazeRowNumber = lineNumber - 3;
                if (mazeRowNumber> dimensions.height) {
                    printLoadFromFileWarning(
                            "Alle Zeilen des Labyrinths, die groesser als die vorgegebenen Zeilenanzahl sind werden ignoriert.",
                            fileName);
                    break;
                }

                int colIndex = 0;
                for (char entity: row) {
                    if(colIndex + 1 > dimensions.width){
                        printLoadFromFileWarning(
                                "Alle Spalten des Labyrinths, die groesser als die vorgegebenen Spaltenanzahl sind werden ignoriert.",
                                fileName);
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
                            rowData.push_back(new  MazeFloor(true));
                            break;
                        default:
                            printLoadFromFileError(
                                    "Im Labyrinth ist ein unbekanntest Zeichen",
                                    fileName);
                            break;
                    }
                    colIndex++;
                }

                while(rowData.size() < dimensions.width){
                    rowData.push_back(new MazeFloor(false));
                }
                data.push_back(rowData);
                mazeRow++;
                break;
        }
        lineNumber++;
    }

    return Maze(data, startPoint, endPoint);
}

