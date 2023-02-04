#include <iostream>
#include "MazeWall.hpp"
#include "MazeFloor.hpp"
#include "Maze.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <vector>


int main() {
    MazeWall wall;
    MazeFloor floorVisited(FLOOR_TPYE::DEFAULT, true);
    MazeFloor floor(FLOOR_TPYE::DEFAULT, false);

    floor.visit();


    std::vector<std::vector<MazeEntity>> m{
            {
                    wall, wall, wall
            },
            {
                    floor, floor, floor
            },
            {
                    floorVisited, floorVisited, floorVisited, wall
            }
    };

    Maze maze(m);
    std::cout << maze;
}
