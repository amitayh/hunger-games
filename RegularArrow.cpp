#include "RegularArrow.h"

RegularArrow::RegularArrow(Player& shooter): Arrow(shooter) {
    color = WHITE;
}

bool RegularArrow::checkHit() {
    if (pSquare && pSquare->hasWall()) {
        hit = true;
    }
    return Arrow::checkHit();
}