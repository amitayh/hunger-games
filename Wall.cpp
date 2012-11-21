#include "Wall.h"

Wall::Wall(Square& square) {
    pSquare = &square;
    square.setWall(*this);
}

void Wall::draw() const {
    pSquare->draw('#', GREY);
}