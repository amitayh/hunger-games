#include "Object.h"

Object::Object() {
    pGame = NULL;
    pSquare = NULL;
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