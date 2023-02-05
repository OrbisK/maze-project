#include <iostream>
#include "MazeWall.hpp"
#include "MazeFloor.hpp"
#include "Maze.hpp"
#include <vector>


int main() {
    MazeWall wall;
    MazeFloor floorVisited(FLOOR_TPYE::DEFAULT, true);
    MazeFloor floor(FLOOR_TPYE::DEFAULT, false);
    MazeFloor start(FLOOR_TPYE::START, false);
    MazeFloor end(FLOOR_TPYE::END, false);

    floor.visit();


    std::vector<std::vector<MazeEntity>> m{
            {
                    wall,         wall,         wall, start
            },
            {
                    floor,        floor,        floor,  end
            },
            {
                    floorVisited, floorVisited, floorVisited, wall
            }
    };

    Maze maze(m, {1,2});
    std::cout << maze;
}
