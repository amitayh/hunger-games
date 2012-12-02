#include "ExplodingArrow.h"
#include "Game.h"

ExplodingArrow::ExplodingArrow(Player& shooter): Arrow(shooter) {
    color = MAGENTA;
}

bool ExplodingArrow::checkHit() {
    if (pSquare && pSquare->hasWall()) {
        pGame->clearWall(*pSquare);
        hit = true;
    }
    return Arrow::checkHit();
}