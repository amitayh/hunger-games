#include "Player.h"
#include "Game.h"
#include "DroppingObject.h"
#include "RegularArrow.h"
#include "ExplodingArrow.h"
#include "PenetratingArrow.h"

Player::Player(char name) {
    this->name = name;
    power = INITIAL_POWER;
    direction = RIGHT;
    arrowsBag.remaining[ArrowsBag::REGULAR] = INITIAL_NUM_REGULAR_ARROWS;
    arrowsBag.remaining[ArrowsBag::EXPLODING] = INITIAL_NUM_EXPLODING_ARROWS;
    arrowsBag.remaining[ArrowsBag::PENETRATING] = INITIAL_NUM_PENETRATING_ARROWS;
    lastArrowTick = 0;
}

Player::~Player() {
    // Clear square before deletion
    pSquare->stepOut(*this);
}

void Player::setSquare(Grid::Square& square) {
    if (square.hasDroppingObject()) {
        // Pick up dropping object
        DroppingObject& droppingObject = square.getDroppingObject();
        droppingObject.affect(*this);
    }

    const List& players = square.getPlayers();
    if (!players.isEmpty()) {
        // Fight other players on square
        List::Iterator it(players);
        while (power > 0 && !it.done()) {
            List::Node* node = it.getCurrent();
            Player* player = (Player*) node->getData();
            fight(*player);
        }
    }

    if (pSquare) {
        pSquare->stepOut(*this);
    }
    square.stepIn(*this);
    pSquare = &square;
}

Grid::Square& Player::getNextMove() {
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

DroppingObject* Player::findClosestObject() const {
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

bool Player::isClearPath(const Grid::Square& target) const {
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

void Player::setRandomDirection() {
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

void Player::shootArrow() {
    shootArrow(arrowsBag.getAvailableType());
}

void Player::shootArrow(ArrowsBag::Type type) {
    Grid::Square& arrowSquare = getNextSquare();
    if (
        !arrowSquare.hasWall() &&                                   // Don't shoot directly at a wall
        arrowsBag.remaining[type] > 0 &&                            // Player still has arrows
        pGame->getTick() > lastArrowTick + MIN_TICKS_BETWEEN_ARROWS // Check minimum ticks between arrows
    ) {
        Arrow* arrow = arrowsBag.getArrow(type);
        arrow->setDirection(direction);
        pGame->addArrow(*arrow, arrowSquare); // Update game
        lastArrowTick = pGame->getTick();
    }
}

bool Player::hasPlayersInRange() const {
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

bool Player::playerInRange(const Player& opponent) const {
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

void Player::fight(Player& opponent) {
    if (power > opponent.getPower()) {
        // Player is stronger than opponent
        opponent.decreasePower(200);
        decreasePower(10);
    } else if (power < opponent.getPower()) {
        // Player is weaker than opponent
        opponent.decreasePower(10);
        decreasePower(200);
    } else {
        // Player and opponent are equally matched
        opponent.decreasePower(50);
        decreasePower(50);
    }
}

void Player::increasePower(int amount) {
    power = __max(power + amount, 0);
}

void Player::decreasePower(int amount) {
    increasePower(-amount);
}

char Player::getName() const {
    return name;
}

int Player::getPower() const {
    return power;
}

Player::ArrowsBag& Player::getArrowsBag() {
    return arrowsBag;
}

void Player::draw() const {
    pSquare->draw(name, CYAN);
}

// Player arrows bag

Player::ArrowsBag::ArrowsBag() {
    remaining[REGULAR] = remaining[EXPLODING] = remaining[PENETRATING] = 0;
}

bool Player::ArrowsBag::isEmpty() const {
    return (remaining[REGULAR] + remaining[EXPLODING] + remaining[PENETRATING] == 0);
}

int Player::ArrowsBag::getRemaining(Type type) const {
    return remaining[type];
}

Player::ArrowsBag::Type Player::ArrowsBag::getAvailableType() const {
    Type result;
    if (!isEmpty()) {
        // Check which arrow type is available
        int available[3], numAvailable = 0, type;
        for (type = 0; type < 3; type++) {
            if (remaining[type] > 0) {
                available[numAvailable] = type;
                numAvailable++;
            }
        }

        // Choose randomly from available types
        int random = rand() % numAvailable;
        result = (Type) available[random];
    }
    return result;
}

Arrow* Player::ArrowsBag::getArrow(Type type) {
    Arrow* arrow = NULL;
    if (remaining[type] > 0) {
        // Allocate arrow
        switch (type) {
            case REGULAR:
                arrow = new RegularArrow;
                break;
            case EXPLODING:
                arrow = new ExplodingArrow;
                break;
            case PENETRATING:
                arrow = new PenetratingArrow;
                break;
        }

        // Decrease counter
        remaining[type]--;
    }
    return arrow;
}

Player::ArrowsBag& Player::ArrowsBag::operator+=(int amount) {
    remaining[REGULAR] += amount;
    remaining[EXPLODING] += amount;
    remaining[PENETRATING] += amount;
    return *this;
}

Player::ArrowsBag& Player::ArrowsBag::operator++() {
    // Add one arrow of each type
    return (*this += 1);
}