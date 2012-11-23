#include "DroppingObject.h"

DroppingObject::DroppingObject(Type type, Grid::Square& square) {
    square.setDroppingObject(*this);
    this->type = type;
    pSquare = &square;
    pickedUp = false;
}

DroppingObject::~DroppingObject() {
    pSquare->unsetDroppingObject();
    pSquare->clear();
}

void DroppingObject::affect(Player& player) {
    switch (type) {
        case FOOD:
            player.increasePower(200);
            break;
        case QUIVER:
            player.addArrows(3);
            break;
        case BOMB:
            player.decreasePower(750);
            break;
    }
    pickedUp = true;
}

Grid::Square& DroppingObject::getSquare() const {
    return *pSquare;
}

void DroppingObject::draw() const {
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
    pSquare->draw(ch, color);
}

bool DroppingObject::getPickedUp() const {
    return pickedUp;
}

DroppingObject::Type DroppingObject::getType() const {
    return type;
}