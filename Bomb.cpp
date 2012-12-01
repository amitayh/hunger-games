#include "Bomb.h"

void Bomb::affect(Player& player) {
    player.decreasePower(750);
    pickedUp = true;
}

void Bomb::draw() const {
    pSquare->draw('@', RED);
}