#include "Square.h"

Square::Square() {
	droppingObject = NULL;
	wall = NULL;
}

void Square::Enter(Player* player) {
	players.push_back(player);
}

void Square::Leave(Player* player) {
	players.remove(player);
}

void Square::Enter(Arrow* arrow) {
	arrows.push_back(arrow);
}

void Square::Leave(Arrow* arrow) {
	arrows.remove(arrow);
}

void Square::SetPosition(int row, int col) {
    this->row = row;
	this->col = col;
}

bool Square::SetDroppingObject(DroppingObject* droppingObject) {
	if (!this->droppingObject) {
		this->droppingObject = droppingObject;
		return true;
	}
	return false;
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