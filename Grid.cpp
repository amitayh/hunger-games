#include "Grid.h"
#include "Player.h"
#include "DroppingObject.h"
#include "Gotoxy.h"
#include <iostream>

using namespace std;

// Grid implementation

Grid::Grid(int rows, int cols): rows(rows), cols(cols) {
    // Allocate squares matrix
    squares = new Square*[rows];
    for (int row = 0; row < rows; row++) {
        squares[row] = new Square[cols];
        for (int col = 0; col < cols; col++) {
            squares[row][col].initPosition(row, col);
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

Grid::Square& Grid::getSquare(int row, int col) const {
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

Grid::Square& Grid::getRandomSquare() const {
    int row = rand() % rows, col = rand() % cols;
    return getSquare(row, col);
}

int Grid::getRows() const {
    return rows;
}

int Grid::getCols() const {
    return cols;
}

// Grid square implementation

Grid::Square::Square() {
    pDroppingObject = NULL;
    pWall = NULL;
}

void Grid::Square::stepIn(const Player& player) {
    players.push(&player);
}

void Grid::Square::stepOut(const Player& player) {
    // The List::find() method performs a linear search (O(n) efficiency), however
    // in most cases the list will not contain more than one player
    List::Node* node = players.find(&player);
    players.remove(node);
}

void Grid::Square::initPosition(int row, int col) {
    this->row = row;
    this->col = col;
}

void Grid::Square::setDroppingObject(DroppingObject& droppingObject) {
    pDroppingObject = &droppingObject;
}

void Grid::Square::unsetDroppingObject() {
    pDroppingObject = NULL;
}

void Grid::Square::setWall(Wall& wall) {
    pWall = &wall;
}

const List& Grid::Square::getPlayers() const {
    return players;
}

DroppingObject& Grid::Square::getDroppingObject() const {
    return *pDroppingObject;
}

void Grid::Square::clear() const {
    if (pDroppingObject) {
        // Draw dropping object
        pDroppingObject->draw();
    } else {
        // Blank square
        draw(' ');
    }
}

bool Grid::Square::hasDroppingObject() const {
    return (pDroppingObject != NULL);
}

bool Grid::Square::hasWall() const {
    return (pWall != NULL);
}

void Grid::Square::draw(char ch, Color color) const {
    // Draw a single character on square
    gotoxy(col, row);
    changeColor(color);
    cout << ch;
}

double Grid::Square::getDistance(const Square& otherSquare) const {
    // Distance function: sqrt(dx^2+dy^2), where dx=x2-x1, dy=y2-y1
    double deltaX = col - otherSquare.getCol(), deltaY = row - otherSquare.getRow();
    return sqrt((deltaX * deltaX) + (deltaY * deltaY));
}

Direction Grid::Square::getDirection(const Square& otherSquare) const {
    // Calculate the average direction from square to otherSquare
    // The center (O) is the square. The function checks in which of the
    // four regions the other square 
    // 
    //  \   ^   /
    //   \  |  / 
    //    \ | /  
    //     \|/   
    // <----O---->
    //     /|\
    //    / | \
    //   /  |  \
    //  /   v   \

    double deltaY = row - otherSquare.getRow(),
           deltaX = col - otherSquare.getCol(),
           angle = atan2(deltaY, deltaX) / PI;

    Direction direction;
    if (angle >= -0.75 && angle < -0.25) {
        direction = DOWN;
    } else if (angle >= -0.25 && angle < 0.25) {
        direction = LEFT;
    } else if (angle >= 0.25 && angle < 0.75) {
        direction = UP;
    } else {
        direction = RIGHT;
    }

    return direction;
}

bool Grid::Square::isEmpty() const {
    // Check if square is not occupied by a dropping object, a wall, or a player
    return (!pDroppingObject && !pWall && players.isEmpty());
}

int Grid::Square::getRow() const {
    return row;
}

int Grid::Square::getCol() const {
    return col;
}