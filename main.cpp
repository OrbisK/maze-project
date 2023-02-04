#include <iostream>
#include "MazeWall.hpp"
#include "MazeFloor.hpp"

int main() {
    MazeWall wall;
    MazeFloor floorVisited(FLOOR_TPYE::DEFAULT, true );
    MazeFloor floor(FLOOR_TPYE::DEFAULT, false );

    std::cout << wall.toString() << floorVisited.toString() << floor.toString();
}
