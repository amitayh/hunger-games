#include "Wall.h"

void Wall::setSquare(Grid::Square& square) {
    Object::setSquare(square);
    square.setWall(*this);
}

void Wall::draw() const {
    pSquare->draw('#', GREY);
}