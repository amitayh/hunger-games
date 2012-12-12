#include "RegularArrow.h"

bool RegularArrow::checkHit() {
    if (pSquare && pSquare->hasWall()) {
        hit = true;
    }
    return Arrow::checkHit();
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