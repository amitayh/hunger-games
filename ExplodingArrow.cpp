#include "ExplodingArrow.h"
#include "Game.h"

using namespace HungerGames;

bool ExplodingArrow::checkHit() {
    if (pSquare && pSquare->hasWall()) {
        pGame->clearWall(pSquare->getWall());
        hit = true;
    }
    return BaseArrow::checkHit();
}

void ExplodingArrow::draw() const {
    pSquare->draw('*', Console::WHITE);
}