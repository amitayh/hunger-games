#include "Wall.h"

Wall::Wall(Square &square) {
    pSquare = &square;
    square.SetWall(*this);
}

void Wall::Draw() const {
    pSquare->Draw('#', GREY);
}