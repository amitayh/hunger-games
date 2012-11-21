#include "Wall.h"

Wall::Wall(Square &square) {
    this->square = &square;
    square.SetWall(*this);
}

void Wall::Draw() const {
    square->Draw('#', GREY);
}