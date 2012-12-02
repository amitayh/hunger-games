#include "Bot.h"
#include "Game.h"

Bot::Bot(char name): Player(name) {}

void Bot::update() {
    if (power > 0) {
        if (pGame->getTick() % MOVE_INTERVAL == 0) {
            // Move to next square
            setSquare(getNextMove());
        }

        if (
            !arrowsBag.isEmpty() &&                             // Player still has arrows
            pGame->checkProbability(SHOOT_ARROW_PROBABILITY) && // Check probability, don't shoot on every chance
            hasPlayersInRange()                                 // Shoot only if there is a reasonable chance of hitting an opponent
        ) {
            // Shoot an arrow if conditions are met
            shootArrow();
        }
    }
}

Grid::Square& Bot::getNextMove() {
    // Find closest food / quiver
    DroppingObject* closest = findClosestObject();
    if (closest && isClearPath(closest->getSquare())) {
        // Move towards the closest if it exists and the path is clear
        direction = pSquare->getDirection(closest->getSquare());
    } else if (pGame->checkProbability(CHANGE_DIRECTION_PROBABILITY)) {
        // Randomly change direction
        setRandomDirection();
    }

    Grid::Square* nextSquare = &getNextSquare();
    while (nextSquare->hasWall()) {
        // Change direction to avoid the wall
        setRandomDirection();
        nextSquare = &getNextSquare();
    }

    return *nextSquare;
}

DroppingObject* Bot::findClosestObject() const {
    DroppingObject* closest = NULL;
    if (!pGame->getDroppingObjects().isEmpty()) {
        double closestDistance = 0;
        List::Iterator it(pGame->getDroppingObjects());
        while (!it.done()) {
            // Iterate over the objects list
            List::Node* node = it.getCurrent();
            DroppingObject* current = (DroppingObject*) node->getData();
            if (current->getType() != DroppingObject::Type::BOMB) {
                // Don't go for the bombs!
                double distance = pSquare->getDistance(current->getSquare());
                if (!closest || distance < closestDistance) {
                    // Found a closer food / quiver - update result
                    closestDistance = distance;
                    closest = current;
                }
            }
        }
    }
    return closest;
}

bool Bot::isClearPath(const Grid::Square& target) const {
    bool result = true;
    Grid::Square* current = pSquare;
    while (result && current != &target) {
        // Simulate the actual movement and check for walls in the path
        Direction direction = current->getDirection(target);
        current = &getNextSquare(pGame->getGrid(), *current, direction);
        if (current != &target && !current->isEmpty()) {
            // Path is not clear
            result = false;
        }
    }
    return result;
}

void Bot::setRandomDirection() {
    // Set a direction randomly. Player will only turn right or left (from his perspective)
    Direction directions[2];
    switch (direction) {
        case UP:
        case DOWN:
            directions[0] = LEFT;
            directions[1] = RIGHT;
            break;
        case LEFT:
        case RIGHT:
            directions[0] = UP;
            directions[1] = DOWN;
            break;
    }
    direction = directions[rand() % 2];
}

bool Bot::hasPlayersInRange() const {
    List::Iterator it(pGame->getPlayers());
    bool inRange = false;
    while (!inRange && !it.done()) {
        // Iterate over the players list
        List::Node* node = it.getCurrent();
        Player* player = (Player*) node->getData();
        if (player != this) {
            // Check if opponent may be hit if an arrow will be shot
            inRange = playerInRange(*player);
        }
    }
    return inRange;
}

bool Bot::playerInRange(const Player& opponent) const {
    // Basic algorithm: check opponent's square and direction.
    // Compare with player's square and direction and decide whether or not to shoot
    const Grid::Square& opponentSquare = opponent.getSquare();
    Direction opponentDirection = opponent.getDirection();

    // Yuck, I know...
    if (
        (direction == RIGHT && pSquare->getCol() < opponentSquare.getCol()) ||
        (direction == LEFT && pSquare->getCol() > opponentSquare.getCol())
    ) {
        if (opponentDirection == DOWN) {
            return (pSquare->getRow() > opponentSquare.getRow());
        } else if (opponentDirection == UP) {
            return (pSquare->getRow() < opponentSquare.getRow());
        } else {
            return (pSquare->getRow() == opponentSquare.getRow());
        }      
    } else if (
        (direction == DOWN && pSquare->getRow() < opponentSquare.getRow()) ||
        (direction == UP && pSquare->getRow() > opponentSquare.getRow())
    ) {
        if (opponentDirection == RIGHT) {
            return (pSquare->getCol() > opponentSquare.getCol());
        } else if (opponentDirection == LEFT) {
            return (pSquare->getCol() < opponentSquare.getCol());
        } else {
            return (pSquare->getCol() == opponentSquare.getCol());
        }
    }

    return false;
}