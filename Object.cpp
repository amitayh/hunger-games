#include "Object.h"

void Object::setSquare(Grid::Square& square) {
    pSquare = &square;
}

Grid::Square& Object::getSquare() const {
    return *pSquare;
}