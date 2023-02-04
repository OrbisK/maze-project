#include "MazeFloor.hpp"

char DEFAULT_SYMBOL = ' ';
char VISITED_SYMBOL = '.';
char START_SYMBOL = 'S';
char END_SYMBOL = 'E';


void MazeFloor::updateSymbol() {
    switch (type) {
        case FLOOR_TPYE::START:
            setDisplaySymbol(START_SYMBOL);
            break;
        case FLOOR_TPYE::END:
            setDisplaySymbol(END_SYMBOL);
            break;
        case FLOOR_TPYE::DEFAULT:
            setDisplaySymbol(getIsVisited() ? VISITED_SYMBOL : DEFAULT_SYMBOL);
            break;
    }
}

bool MazeFloor::visit() {
    if (getIsSolid()) {
        return false;
    }
    setIsVisited(true);
    updateSymbol();
    return true;
}

MazeFloor::MazeFloor(FLOOR_TPYE t, bool visited) : MazeEntity(DEFAULT_SYMBOL, false, visited) {
    type = t;
    updateSymbol();
}

