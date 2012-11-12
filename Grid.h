#ifndef _GRID_H
#define _GRID_H

#include "Square.h"

const int DEFAULT_NUM_ROWS = 24;
const int DEFAULT_NUM_COLS = 79;

class Grid
{
    int rows, cols;
    Square** squares;

public:
    Grid(int rows, int cols);
    ~Grid();
    
    int GetRows();
    int GetCols();
    Square* GetSquare(int row, int col);
    Square* GetRandomSquare();
};

#endif