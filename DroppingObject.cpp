#include "DroppingObject.h"

DroppingObject::DroppingObject() {
    pickedUp = false;
}

DroppingObject::~DroppingObject() {
    pSquare->unsetDroppingObject();
    pSquare->clear();
}

void DroppingObject::setSquare(Grid::Square& square) {
    Object::setSquare(square);
    square.setDroppingObject(*this);
}

bool DroppingObject::getPickedUp() const {
    return pickedUp;
}

DroppingObject::Type DroppingObject::getType() const {
    return type;
}