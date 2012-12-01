#include "Object.h"

Object::Object() {
    pGame = NULL;
    pSquare = NULL;
}

Object::~Object() {
    if (pSquare) {
        pSquare->clear();
    }
}

void Object::setGame(Game& game) {
    pGame = &game;
}

void Object::setSquare(Grid::Square& square) {
    pSquare = &square;
}

Grid::Square& Object::getSquare() const {
    return *pSquare;
}