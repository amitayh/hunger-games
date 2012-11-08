#include "Grid.h"

Grid::Grid() {
    rows = cols = 0;
}

Grid::~Grid() {
	for (int row = 0; row < rows; row++) {
		delete []squares[row];
        squares[row] = NULL;
	}
	delete []squares;
    squares = NULL;
}

void Grid::Init(int rows, int cols) {
	this->rows = rows;
	this->cols = cols;
	squares = new Square*[rows];
	for (int row = 0; row < rows; row++) {
		squares[row] = new Square[cols];
        for (int col = 0; col < cols; col++) {
            squares[row][col].SetPosition(row, col);
        }
	}
}

int Grid::GetRows() {
    return rows;
}

int Grid::GetCols() {
    return cols;
}

Square* Grid::GetSquare(int row, int col) {
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
	return &squares[row][col];
}