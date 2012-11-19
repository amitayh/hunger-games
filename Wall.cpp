#include "Wall.h"

void Wall::SetSquare(Square* square) {
    this->square = square;
    square->SetWall(this);
}

void Wall::Draw() const {
    square->Draw('#', GREY);
}