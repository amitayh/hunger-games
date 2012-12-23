#include "Quiver.h"
#include "BasePlayer.h"

using namespace HungerGames;

Quiver::Quiver() {
    type = QUIVER;
}

void Quiver::affect(BasePlayer& player) {
    ++player.getArrowsBag();
    pickedUp = true;
}

void Quiver::draw() const {
    pSquare->draw('*', Console::YELLOW);
}