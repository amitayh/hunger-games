#include "Wall.h"

Wall::Wall(Grid::Square& square) {
    pSquare = &square;
    square.setWall(*this);
}

void Wall::draw() const {
    pSquare->draw('#', GREY);
}