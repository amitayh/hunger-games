#include "RegularArrow.h"

using namespace HungerGames;

bool RegularArrow::checkHit() {
    if (pSquare && pSquare->hasWall()) {
        hit = true;
    }
    return BaseArrow::checkHit();
}

void RegularArrow::draw() const {
    char ch;
    switch (direction) {
        case UP:
            ch = '^';
            break;
        case DOWN:
            ch = 'v';
            break;
        case LEFT:
            ch = '<';
            break;
        case RIGHT:
            ch = '>';
            break;
    }
    pSquare->draw(ch, Console::WHITE);
}