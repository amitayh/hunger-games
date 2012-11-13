#ifndef _GRID_H
#define _GRID_H

#include "Square.h"

class Grid
{
    int rows, cols;
    Square** squares;

public:
    static const int DEFAULT_NUM_ROWS;
    static const int DEFAULT_NUM_COLS;

    Grid(int rows = DEFAULT_NUM_ROWS, int cols = DEFAULT_NUM_COLS);
    ~Grid();
    
    int GetRows();
    int GetCols();
    Square* GetSquare(int row, int col);
    Square* GetRandomSquare();
};

#endif