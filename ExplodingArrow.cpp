#include "ExplodingArrow.h"
#include "Game.h"

ExplodingArrow::ExplodingArrow() {
    color = MAGENTA;
}

bool ExplodingArrow::checkHit() {
    if (pSquare && pSquare->hasWall()) {
        pGame->clearWall(*pSquare);
        hit = true;
    }
    return Arrow::checkHit();
}