#include "Object.h"

Object::Object() {
    pSquare = NULL;
}

Object::~Object() {
    if (pSquare) {
        pSquare->clear();
    }
}

void Object::setSquare(Grid::Square& square) {
    pSquare = &square;
}

Grid::Square& Object::getSquare() const {
    return *pSquare;
}