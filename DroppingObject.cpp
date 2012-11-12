#include "DroppingObject.h"
#include "Square.h"

DroppingObject::DroppingObject() {
    pickedUp = false;
}

DroppingObject::~DroppingObject() {
    Square* square = GetSquare();
    if (square) {
        square->SetDroppingObject(NULL);
    }
}

void DroppingObject::SetSquare(Square* square) {
    square->SetDroppingObject(this);
    Object::SetSquare(square);
}

void DroppingObject::Affect(Player* player) {
    pickedUp = true;
}

bool DroppingObject::GetPickedUp() {
    return pickedUp;
}