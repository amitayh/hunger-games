#include "Wall.h"

void Wall::setSquare(Grid::Square& square) {
    BaseObject::setSquare(square);
    square.setWall(*this);
}

void Wall::draw() const {
    pSquare->draw('#', Console::GREY);
}