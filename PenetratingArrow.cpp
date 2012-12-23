#include "PenetratingArrow.h"

using namespace HungerGames;

void PenetratingArrow::draw() const {
    char ch;
    switch (direction) {
        case UP:
        case DOWN:
            ch = '|';
            break;
        case LEFT:
        case RIGHT:
            ch = '-';
            break;
    }
    pSquare->draw(ch, Console::WHITE);
}