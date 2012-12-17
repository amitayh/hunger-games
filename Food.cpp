#include "Food.h"

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