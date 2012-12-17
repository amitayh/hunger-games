#include "BaseObject.h"

BaseObject::BaseObject() {
    pGame = NULL;
    pSquare = NULL;
}

void BaseObject::setGame(Game& game) {
    pGame = &game;
}

void BaseObject::setSquare(Grid::Square& square) {
    pSquare = &square;
}

Grid::Square& BaseObject::getSquare() const {
    return *pSquare;
}