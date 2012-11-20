#include "DroppingObject.h"
#include "Square.h"

DroppingObject::DroppingObject(Type type, Square *square) {
    square->SetDroppingObject(*this);
    this->square = square;
    this->type = type;
    pickedUp = false;
}

DroppingObject::~DroppingObject() {
    square->UnsetDroppingObject();
    square->Clear();
}

void DroppingObject::Affect(Player &player) {
    switch (type) {
        case FOOD:
            player.IncreasePower(200);
            break;
        case QUIVER:
            player.AddArrows(3);
            break;
        case BOMB:
            player.DecreasePower(750);
            break;
    }
    pickedUp = true;
}

Square *DroppingObject::GetSquare() {
    return square;
}

void DroppingObject::Draw() const {
    char ch;
    Color color;
    switch (type) {
        case FOOD:
            ch = '$';
            color = LIME;
            break;
        case QUIVER:
            ch = '*';
            color = YELLOW;
            break;
        case BOMB:
            ch = '@';
            color = RED;
            break;
    }
    square->Draw(ch, color);
}

bool DroppingObject::GetPickedUp() const {
    return pickedUp;
}

DroppingObject::Type DroppingObject::GetType() const {
    return type;
}