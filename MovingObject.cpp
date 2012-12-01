#include "MovingObject.h"

Direction MovingObject::getDirection() const {
    return direction;
}

Grid::Square& MovingObject::getNextSquare(const Grid& grid) const {
    return getNextSquare(grid, *pSquare, direction);
}

Grid::Square& MovingObject::getNextSquare(const Grid& grid, const Grid::Square& square, Direction direction) {
    int row = square.getRow(), col = square.getCol();
    switch (direction) {
        case UP:
            row--;
            break;
        case DOWN:
            row++;
            break;
        case LEFT:
            col--;
            break;
        case RIGHT:
            col++;
            break;
    }
    return grid.getSquare(row, col);
}