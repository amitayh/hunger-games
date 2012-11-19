#include "Square.h"
#include "Player.h"
#include "DroppingObject.h"
#include <windows.h>
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

List* Square::GetPlayers() {
    return &players;
}

DroppingObject* Square::GetDroppingObject() {
    return droppingObject;
}

Wall* Square::GetWall() {
    return wall;
}

void Square::Clear() const {
    if (droppingObject) {
        droppingObject->Draw();
    } else {
        Draw(' ');
    }
}

void Square::Draw(char ch, Color color) const {
    gotoxy(col, row);
    ChangeColor(color);
    cout << ch;
}

double Square::GetDistance(const Square* otherSquare) const {
    double deltaX = col - otherSquare->GetCol(), deltaY = row - otherSquare->GetRow();
    return sqrt((deltaX * deltaX) + (deltaY * deltaY));
}

bool Square::IsEmpty() const {
    return (!droppingObject && !wall && players.IsEmpty());
}

int Square::GetRow() const {
    return row;
}

int Square::GetCol() const {
    return col;
}