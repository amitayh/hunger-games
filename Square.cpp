#include "Square.h"
#include "Player.h"
#include <math.h>

Square::Square() {
    droppingObject = NULL;
    wall = NULL;
}

void Square::StepIn(Player* player) {
    players.push_front(player);
}

void Square::StepOut(Player* player) {
    players.remove(player);
}

void Square::SetPosition(int row, int col) {
    this->row = row;
    this->col = col;
}

void Square::SetDroppingObject(DroppingObject* droppingObject) {
    this->droppingObject = droppingObject;
}

void Square::SetWall(Wall* wall) {
    this->wall = wall;
}

int Square::GetRow() {
    return row;
}

int Square::GetCol() {
    return col;
}

PlayersList* Square::GetPlayers() {
    return &players;
}

DroppingObject* Square::GetDroppingObject() {
    return droppingObject;
}

Wall* Square::GetWall() {
    return wall;
}

double Square::GetDistance(Square* otherSquare) {
    double deltaX = col - otherSquare->GetCol(), deltaY = row - otherSquare->GetRow();
    return sqrt((deltaX * deltaX) + (deltaY * deltaY));
}

bool Square::IsEmpty() {
    return (!droppingObject && !wall && players.empty());
}