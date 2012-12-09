#include "Food.h"

Food::Food() {
    type = FOOD;
}

void Food::affect(Player& player) {
    player.increasePower(200);
    pickedUp = true;
}

void Food::draw() const {
    pSquare->draw('$', LIME);
}