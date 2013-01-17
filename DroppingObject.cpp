#include "DroppingObject.h"
#include "Game.h"

using namespace HungerGames;

DroppingObject::DroppingObject() {
    pickedUp = false;
}

DroppingObject::~DroppingObject() {
    if (pGame && pGame->isRunning()) {
        pSquare->unsetDroppingObject();
    }
}

void DroppingObject::setSquare(Grid::Square& square) {
    BaseObject::setSquare(square);
    square.setDroppingObject(*this);
    draw(); // Draw immediately when the object is dropped
}

bool DroppingObject::getPickedUp() const {
    return pickedUp;
}

DroppingObject::Type DroppingObject::getType() const {
    return type;
}