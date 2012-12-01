#include "Arrow.h"
#include "Game.h"
#include "Player.h"

Arrow::Arrow(Player& shooter) {
    direction = shooter.getDirection();
    hit = false;
}

Arrow::~Arrow() {
    // Clear square before deletion
    pSquare->clear();
}

void Arrow::setSquare(Grid::Square& square) {
    if (square.hasWall()) {
        // Arrow hit a wall
        hit = true;
    } else {
        // Move to next square
        pSquare = &square;
        checkHit();
    }
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
        const List& players = pSquare->getPlayers();
        if (!players.isEmpty()) {
            // Hit first player on square
            Player* player = (Player*) players.peek();
            player->decreasePower(500);
            hit = true;
        }
    }
    return hit;
}

void Arrow::draw() const {
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
    pSquare->draw(ch, WHITE);
}

bool Arrow::getHit() const {
    return hit;
}