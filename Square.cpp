#include "Square.h"
#include "Player.h"
#include "MovingObject.h"
#include "DroppingObject.h"
#include "Gotoxy.h"
#include <iostream>
#include <windows.h>
#include <math.h>

using namespace std;

Square::Square() {
    pDroppingObject = NULL;
    pWall = NULL;
}

void Square::stepIn(const Player& player) {
    players.push(&player);
}

void Square::stepOut(const Player& player) {
    ListNode* node = players.find(&player);
    players.remove(node);
}

void Square::initPosition(int row, int col) {
    this->row = row;
    this->col = col;
}

void Square::setDroppingObject(DroppingObject& droppingObject) {
    pDroppingObject = &droppingObject;
}

void Square::unsetDroppingObject() {
    pDroppingObject = NULL;
}

void Square::setWall(Wall& wall) {
    pWall = &wall;
}

const List& Square::getPlayers() const {
    return players;
}

DroppingObject& Square::getDroppingObject() const {
    return *pDroppingObject;
}

void Square::clear() const {
    if (pDroppingObject) {
        // Draw dropping object
        pDroppingObject->draw();
    } else {
        // Blank square
        draw(' ');
    }
}

bool Square::hasDroppingObject() const {
    return (pDroppingObject != NULL);
}

bool Square::hasWall() const {
    return (pWall != NULL);
}

void Square::draw(char ch, Color color) const {
    gotoxy(col, row);
    changeColor(color);
    cout << ch;
}

double Square::getDistance(const Square& otherSquare) const {
    // Distance function: sqrt(dx^2+dy^2), where dx=x2-x1, dy=y2-y1
    double deltaX = col - otherSquare.getCol(), deltaY = row - otherSquare.getRow();
    return sqrt((deltaX * deltaX) + (deltaY * deltaY));
}

Direction Square::getDirection(const Square& otherSquare) const {
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

bool Square::isEmpty() const {
    return (!pDroppingObject && !pWall && players.isEmpty());
}

int Square::getRow() const {
    return row;
}

int Square::getCol() const {
    return col;
}