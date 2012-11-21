#include "Grid.h"

Grid::Grid(int rows, int cols): rows(rows), cols(cols) {
    squares = new Square*[rows];
    for (int row = 0; row < rows; row++) {
        squares[row] = new Square[cols];
        for (int col = 0; col < cols; col++) {
            squares[row][col].InitPosition(row, col);
        }
    }
}

Grid::~Grid() {
    for (int row = 0; row < rows; row++) {
        delete []squares[row];
    }
    delete []squares;
}

int Grid::GetRows() {
    return rows;
}

int Grid::GetCols() {
    return cols;
}

Square &Grid::GetSquare(int row, int col) {
    if (row >= rows) {
        row %= rows;
    } else if (row < 0) {
        row = rows + row;
    }
    if (col >= cols) {
        col %= cols;
    } else if (col < 0) {
        col = cols + col;
    }
    return squares[row][col];
}

Square &Grid::GetRandomSquare() {
    int row = rand() % rows, col = rand() % cols;
    return GetSquare(row, col);
}