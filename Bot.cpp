#include "Bot.h"
#include "Common.h"
#include "Game.h"
#include "DroppingObject.h"

using namespace HungerGames;

const int Bot::CHANGE_DIRECTION_PROBABILITY = 10;
const int Bot::SHOOT_ARROW_PROBABILITY      = 20;

Bot::Bot(char name, Console::Color color): BasePlayer(name, color) {}

void Bot::update() {
    if (pGame->getTick() % MOVE_INTERVAL == 0) {
        // Don't call this method on every tick for efficiency reasons
        setNextMove();
    }
    if (
        !arrowsBag.isEmpty() &&                      // Player still has arrows
        checkProbability(SHOOT_ARROW_PROBABILITY) && // Check probability, don't shoot on every chance
        hasPlayersInRange()                          // Shoot only if there is a reasonable chance of hitting an opponent
    ) {
        // Shoot an arrow if conditions are met
        nextArrowType = arrowsBag.getAvailableRandomType();
    } else {
        nextArrowType = ArrowsBag::NONE;
    }
    // Call overridden method
    BasePlayer::update();
}

void Bot::setNextMove() {
    // Find closest food / quiver
    DroppingObject* closest = findClosestObject();
    if (closest && isClearPath(closest->getSquare())) {
        // Move towards the closest if it exists and the path is clear
        direction = pSquare->getDirection(closest->getSquare());
    } else if (checkProbability(CHANGE_DIRECTION_PROBABILITY)) {
        // Randomly change direction
        setRandomDirection();
    }

    Grid::Square* nextSquare = &getNextSquare();
    while (nextSquare->hasWall()) {
        // Change direction to avoid the wall
        setRandomDirection();
        nextSquare = &getNextSquare();
    }
}

DroppingObject* Bot::findClosestObject() const {
    DroppingObjectsList& droppingObjects = pGame->getDroppingObjects();
    DroppingObject* closest = NULL;
    if (!droppingObjects.empty()) {
        double closestDistance = 0;
        DroppingObjectsList::iterator it = droppingObjects.begin();
        while (it != droppingObjects.end()) {
            // Iterate over the objects list
            DroppingObject* current = *it;
            if (current->getType() != DroppingObject::BOMB) {
                // Don't go for the bombs!
                double distance = pSquare->getDistance(current->getSquare());
                if (!closest || distance < closestDistance) {
                    // Found a closer food / quiver - update result
                    closestDistance = distance;
                    closest = current;
                }
            }
            ++it;
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
    PlayersList& players = pGame->getPlayers();
    PlayersList::iterator it = players.begin();
    bool inRange = false;
    while (!inRange && it != players.end()) {
        // Iterate over the players list
        BasePlayer* player = *it;
        if (player != this) {
            // Check if opponent may be hit if an arrow will be shot
            inRange = playerInRange(*player);
        }
        ++it;
    }
    return inRange;
}

bool Bot::playerInRange(const BasePlayer& opponent) const {
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