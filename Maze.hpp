#include "MazeEntity.hpp"
#include<vector>

class Maze {
private:
    std::vector<std::vector<MazeEntity>> maze;

public:
    Maze(std::vector<std::vector<MazeEntity>> &maze);

    friend std::ostream &operator<<(std::ostream &os, const Maze &m);

};
