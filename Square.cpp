#include "Square.h"

Square::Square() {
    item = NULL;
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

void Square::SetItem(Item* item) {
    this->item = item;
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

Item* Square::GetItem() {
    return item;
}

Wall* Square::GetWall() {
    return wall;
}

bool Square::IsEmpty() {
    return (!item && !wall && players.empty());
}