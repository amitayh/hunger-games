#include "Arrow.h"
#include "Game.h"
#include "Player.h"

const int Arrow::MOVE_INTERVAL = 1;

Arrow::Arrow() {
    hit = false;
}

Arrow::~Arrow() {
    // Clear square before deletion
    pSquare->clear();
}

void Arrow::setSquare(Grid::Square& square) {
    pSquare = &square;
    checkHit();
}

void Arrow::update() {
    if (!checkHit() && pGame->getTick() % MOVE_INTERVAL == 0) {
        Grid::Square& nextSquare = getNextSquare();
        pSquare->clear();
        setSquare(nextSquare);
    }
}

bool Arrow::checkHit() {
    if (pSquare) {
        ObjectsList& players = pSquare->getPlayers();
        if (!players.empty()) {
            // Hit first player on square
            Player* player = (Player*) players.front();
            player->decreasePower(500);
            hit = true;
        }
    }
    return hit;
}

bool Arrow::getHit() const {
    return hit;
}