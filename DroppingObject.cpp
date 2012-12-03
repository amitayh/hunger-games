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
    draw(); // Draw immediately when the object is dropped
}

bool DroppingObject::getPickedUp() const {
    return pickedUp;
}

DroppingObject::Type DroppingObject::getType() const {
    return type;
}