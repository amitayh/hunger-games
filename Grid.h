#ifndef _GRID_H
#define _GRID_H

#include "Square.h"

class Grid
{
    enum {
        DEFAULT_NUM_ROWS = 24,
        DEFAULT_NUM_COLS = 79
    };

    int rows, cols;
    Square** squares;

public:
    Grid(int rows = DEFAULT_NUM_ROWS, int cols = DEFAULT_NUM_COLS);
    ~Grid();
    
    Square& getSquare(int row, int col) const;
    Square& getRandomSquare() const;
    int getRows() const;
    int getCols() const;
};

#endif