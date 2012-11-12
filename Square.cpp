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

double Square::GetDistance(Square* square) {
    double deltaX = col - square->GetCol(), deltaY = row - square->GetRow();
    return sqrt((deltaX * deltaX) + (deltaY * deltaY));
}

bool Square::IsEmpty() {
    return (!droppingObject && !wall && players.empty());
}

Player* Square::GetStrongestPlayer() {
    if (!players.empty()) {
        Player *strongest = players.front(), *challenger;
        PlayersIterator it = players.begin();
        while (it != players.end()) {
            challenger = *it;
            if (challenger->GetPower() > strongest->GetPower()) {
                strongest = challenger;
            }
            it++;
        }
        return strongest;
    }
    return NULL;
}