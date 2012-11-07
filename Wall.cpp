#include "Wall.h"
#include "Square.h"

Wall::Wall() {
    SetType(WALL);
}

void Wall::Draw() {
	GotoPosition();
	cout << '#';
}

bool Wall::SetSquare(Square* square) {
    square->SetWall(this);
    return Object::SetSquare(square);
}