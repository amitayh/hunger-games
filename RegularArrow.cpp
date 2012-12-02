#include "RegularArrow.h"

RegularArrow::RegularArrow() {
    color = WHITE;
}

bool RegularArrow::checkHit() {
    if (pSquare && pSquare->hasWall()) {
        hit = true;
    }
    return Arrow::checkHit();
}