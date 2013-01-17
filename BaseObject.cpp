#include "BaseObject.h"

using namespace HungerGames;

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

void BaseObject::Draw::operator()(BaseObject* object) const {
    object->draw();
}

void BaseObject::Delete::operator()(BaseObject* object) const {
    delete object;
}