#include "ExplodingArrow.h"
#include "Game.h"

bool ExplodingArrow::checkHit() {
    if (pSquare && pSquare->hasWall()) {
        pGame->clearWall(*pSquare);
        hit = true;
    }
    return Arrow::checkHit();
}

void ExplodingArrow::draw() const {
    pSquare->draw('*', Console::WHITE);
}