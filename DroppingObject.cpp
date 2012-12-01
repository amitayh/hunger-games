#include "DroppingObject.h"

DroppingObject::DroppingObject() {
    pickedUp = false;
}

DroppingObject::~DroppingObject() {
    pSquare->unsetDroppingObject();
    pSquare->clear();
}

void DroppingObject::setSquare(Grid::Square& square) {
    square.setDroppingObject(*this);
    pSquare = &square;
}

Grid::Square& DroppingObject::getSquare() const {
    return *pSquare;
}

bool DroppingObject::getPickedUp() const {
    return pickedUp;
}