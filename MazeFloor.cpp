#include "MazeFloor.hpp"

bool MazeFloor::visit() {
    if (getIsSolid()) {
        return false;
    }
    setIsVisited(true);
    return true;
}

MazeFloor::MazeFloor(bool visited) : MazeEntity(FLOOR_DEFAULT_SYMBOL, false, visited) {
}
