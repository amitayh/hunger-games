#include "MovingObject.h"

Square &GetNextSquare(Grid &grid, const Square &square, Direction direction) {
    int row = square.GetRow(), col = square.GetCol();
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
    return grid.GetSquare(row, col);
}