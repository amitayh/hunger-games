#include "Square.h"
#include "Player.h"
#include <math.h>

Square::Square() {
    droppingObject = NULL;
    wall = NULL;
}

void Square::StepIn(Player* player) {
    players.Push(player);
}

void Square::StepOut(Player* player) {
    ListNode* node = players.Find(player);
    players.Remove(node);
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

List* Square::GetPlayers() {
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
    return (!droppingObject && !wall && players.IsEmpty());
}