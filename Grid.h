#ifndef _GRID_H
#define _GRID_H

#include "Square.h"

const int DEFAULT_NUM_ROWS = 24;
const int DEFAULT_NUM_COLS = 80;

class Grid
{
    int rows, cols;
    Square** squares;

public:
    Grid();
    ~Grid();
    
    void Init(int rows, int cols);
    int GetRows();
    int GetCols();
    Square* GetSquare(int row, int col);
};

#endif