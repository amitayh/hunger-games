#include "Square.h"
#include "Player.h"

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

bool Square::IsEmpty() {
    return (!droppingObject && !wall && players.empty());
}

void Square::Battle() {
    if (!players.empty()) {
        Player* player;
        Player* strongest = players.front();
        PlayersIterator it = players.begin();
        while (it != players.end()) {
            player = *it;
            if (player->GetPower() > strongest->GetPower()) {
                strongest = player;
            }
            it++;
        }

        /*
        it = players.begin();
        while (it != players.end()) {
            player = *it;
            if (player->GetPower() == strongest->GetPower()) {
                strongest = player;
            }
            it++;
        }
        */

    }
}