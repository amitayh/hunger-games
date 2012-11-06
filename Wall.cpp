#include "Wall.h"

Wall::Wall() {
    SetType(WALL);
}

void Wall::Draw() {
	GotoPosition();
	cout << '#';
}