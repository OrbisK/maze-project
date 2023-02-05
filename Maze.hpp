#include "MazeEntity.hpp"
#include<vector>
#include <tuple>

class Maze {
private:
    std::vector<std::vector<MazeEntity>> maze;
    std::tuple<int, int> playerPosition;
public:
    Maze(std::vector<std::vector<MazeEntity>> &maze, std::tuple<int, int> player);
    friend std::ostream &operator<<(std::ostream &os, Maze &m);
    std::vector<std::vector<MazeEntity>> getMaze();
    int getPlayerPositionX();
    int getPlayerPositionY();
};
