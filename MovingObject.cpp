#include "MovingObject.h"

MovingObject::MovingObject() {
    moveInterval = 1;
}

MovingObject::~MovingObject() {
    // Clear square before deletion
    pSquare->clear();
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

MovingObject::Direction MovingObject::getDirection() const {
    return direction;
}