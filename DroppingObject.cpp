#include "DroppingObject.h"
#include "Square.h"

DroppingObject::DroppingObject() {
    pickedUp = false;
}

void DroppingObject::Affect(Player* player) {
    pickedUp = true;
}

bool DroppingObject::Update() {
    return !pickedUp;
}