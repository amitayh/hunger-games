#include "Food.h"
#include "BasePlayer.h"

using namespace HungerGames;

Food::Food() {
    type = FOOD;
}

void Food::affect(BasePlayer& player) {
    player.increasePower(200);
    pickedUp = true;
}

void Food::draw() const {
    pSquare->draw('$', Console::LIME);
}