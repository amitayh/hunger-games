#include "BaseArrow.h"
#include "Game.h"
#include "BasePlayer.h"

using namespace HungerGames;

const int BaseArrow::MOVE_INTERVAL = 1;

BaseArrow::BaseArrow() {
    hit = false;
}

BaseArrow::~BaseArrow() {
    if (pGame && pGame->isRunning()) {
        // Clear square before deletion
        pSquare->clear();
    }
}

void BaseArrow::setSquare(Grid::Square& square) {
    pSquare = &square;
    checkHit();
}

void BaseArrow::update() {
    if (!checkHit() && pGame->getTick() % MOVE_INTERVAL == 0) {
        Grid::Square& nextSquare = getNextSquare();
        pSquare->clear();
        setSquare(nextSquare);
    }
}

bool BaseArrow::checkHit() {
    if (pSquare) {
        PlayersList& players = pSquare->getPlayers();
        if (!players.empty()) {
            // Hit first player on square
            players.front()->decreasePower(500);
            hit = true;
        }
    }
    return hit;
}

bool BaseArrow::getHit() const {
    return hit;
}