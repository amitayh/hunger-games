#include "MovingObject.h"

Square& getNextSquare(const Grid& grid, const Square& square, Direction direction) {
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