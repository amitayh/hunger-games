#include "Bomb.h"

void Bomb::affect(Player& player) {
    player.increasePower(200);
    pickedUp = true;
}

void Bomb::draw() const {
    pSquare->draw('@', RED);
}