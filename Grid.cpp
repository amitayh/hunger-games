#include "Grid.h"

Grid::Grid(int rows, int cols): rows(rows), cols(cols) {
    // Allocate squares matrix
    squares = new Square*[rows];
    for (int row = 0; row < rows; row++) {
        squares[row] = new Square[cols];
        for (int col = 0; col < cols; col++) {
            squares[row][col].InitPosition(row, col);
        }
    }
}

Grid::~Grid() {
    // Delete squares matrix
    for (int row = 0; row < rows; row++) {
        delete []squares[row];
    }
    delete []squares;
}

Square &Grid::GetSquare(int row, int col) const {
    // Stay in grid's boundaries
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

Square &Grid::GetRandomSquare() const {
    int row = rand() % rows, col = rand() % cols;
    return GetSquare(row, col);
}

int Grid::GetRows() const {
    return rows;
}

int Grid::GetCols() const {
    return cols;
}