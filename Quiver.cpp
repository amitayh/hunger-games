#include "Quiver.h"

Quiver::Quiver() {
    type = QUIVER;
}

void Quiver::affect(Player& player) {
    player.addArrows(3);
    pickedUp = true;
}

void Quiver::draw() const {
    pSquare->draw('*', YELLOW);
}