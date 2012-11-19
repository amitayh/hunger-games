#include "Wall.h"

Wall::Wall(Square *square) {
    this->square = square;
    square->SetWall(this);
}

Wall::~Wall() {
    square->SetWall(NULL);
}

void Wall::Draw() const {
    square->Draw('#', GREY);
}