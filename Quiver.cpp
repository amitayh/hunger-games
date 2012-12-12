#include "Quiver.h"

Quiver::Quiver() {
    type = QUIVER;
}

void Quiver::affect(Player& player) {
    ++player.getArrowsBag();
    pickedUp = true;
}

void Quiver::draw() const {
    pSquare->draw('*', Console::YELLOW);
}