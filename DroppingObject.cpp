#include "DroppingObject.h"
#include "Square.h"

DroppingObject::DroppingObject() {
	pickedUp = false;
}

void DroppingObject::Affect(Player* player) {
	Square* square = GetSquare();
	square->SetDroppingObject(NULL);
	pickedUp = true;
}

bool DroppingObject::Update() {
	return !pickedUp;
}