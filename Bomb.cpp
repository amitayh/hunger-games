#include "Bomb.h"
#include "BasePlayer.h"

using namespace HungerGames;

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