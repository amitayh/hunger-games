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

void Square::StepIn(const Player &player) {
    players.Push(&player);
}

void Square::StepOut(const Player &player) {
    ListNode *node = players.Find(&player);
    players.Remove(node);
}

void Square::InitPosition(int row, int col) {
    this->row = row;
    this->col = col;
}

void Square::SetDroppingObject(DroppingObject &droppingObject) {
    pDroppingObject = &droppingObject;
}

void Square::UnsetDroppingObject() {
    pDroppingObject = NULL;
}

void Square::SetWall(Wall &wall) {
    pWall = &wall;
}

const List &Square::GetPlayers() const {
    return players;
}

DroppingObject &Square::GetDroppingObject() const {
    return *pDroppingObject;
}

void Square::Clear() const {
    if (pDroppingObject) {
        // Draw dropping object
        pDroppingObject->Draw();
    } else {
        // Blank square
        Draw(' ');
    }
}

bool Square::HasDroppingObject() const {
    return (pDroppingObject != NULL);
}

bool Square::HasWall() const {
    return (pWall != NULL);
}

void Square::Draw(char ch, Color color) const {
    gotoxy(col, row);
    ChangeColor(color);
    cout << ch;
}

double Square::GetDistance(const Square &otherSquare) const {
    // Distance function: sqrt(dx^2+dy^2), where dx=x2-x1, dy=y2-y1
    double deltaX = col - otherSquare.GetCol(), deltaY = row - otherSquare.GetRow();
    return sqrt((deltaX * deltaX) + (deltaY * deltaY));
}

Direction Square::GetDirection(const Square &otherSquare) const {
    double deltaY = row - otherSquare.GetRow(),
           deltaX = col - otherSquare.GetCol(),
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

bool Square::IsEmpty() const {
    return (!pDroppingObject && !pWall && players.IsEmpty());
}

int Square::GetRow() const {
    return row;
}

int Square::GetCol() const {
    return col;
}