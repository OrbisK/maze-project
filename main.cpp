#include <iostream>
#include "MazeWall.hpp"
#include "MazeFloor.hpp"
#include "Maze.hpp"
#include "Game.hpp"
#include <vector>


int main() {
//    MazeWall wall;
//    MazeFloor floorVisited(FLOOR_TPYE::DEFAULT, true);
//    MazeFloor floor(FLOOR_TPYE::DEFAULT, false);
//    MazeFloor start(FLOOR_TPYE::START, false);
//    MazeFloor end(FLOOR_TPYE::END, false);
//
//    floor.visit();
//
//
//    std::vector<std::vector<MazeEntity>> m{
//            {
//                    wall,         wall,         wall,         start
//            },
//            {
//                    floor,        floor,        floor,        end
//            },
//            {
//                    floorVisited, floorVisited, floorVisited, wall
//            }
//    };
//    std::tuple<int, int> pos = std::make_tuple(0,0);
//    Maze maze(m, pos);
//    maze.getPlayer().move(DOWN);
//
//    Game g(maze);
    Maze m = Maze::loadFromFile("levels/1.txt");
    std::cout << m;

}
