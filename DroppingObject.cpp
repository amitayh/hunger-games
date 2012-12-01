#include "DroppingObject.h"

DroppingObject::DroppingObject() {
    pickedUp = false;
}

DroppingObject::~DroppingObject() {
    pSquare->unsetDroppingObject();
    pSquare->clear();
}

bool DroppingObject::getPickedUp() const {
    return pickedUp;
}