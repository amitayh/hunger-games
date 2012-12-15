#include "ExplodingArrow.h"
#include "Game.h"

bool ExplodingArrow::checkHit() {
    if (pSquare && pSquare->hasWall()) {
        pGame->clearWall(pSquare->getWall());
        hit = true;
    }
    return Arrow::checkHit();
}

void ExplodingArrow::draw() const {
    pSquare->draw('*', Console::WHITE);
}