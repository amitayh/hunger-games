#include "Bomb.h"
#include "BasePlayer.h"

Bomb::Bomb() {
    type = BOMB;
}

void Bomb::affect(BasePlayer& player) {
    player.decreasePower(750);
    pickedUp = true;
}

void Bomb::draw() const {
    pSquare->draw('@', Console::RED);
}