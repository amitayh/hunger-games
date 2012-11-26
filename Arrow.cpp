#include "Arrow.h"
#include "Player.h"
#include "Game.h"

Arrow::Arrow(Player& shooter) {
    direction = shooter.getDirection();
    hit = false;
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

void Arrow::move(Game& game) {
    if (!checkHit() && game.getTick() % moveInterval == 0) {
        Grid::Square& nextSquare = MovingObject::getNextSquare(game.getGrid(), *pSquare, direction);
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