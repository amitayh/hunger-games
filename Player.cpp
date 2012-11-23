#include "Player.h"
#include "Game.h"
#include "DroppingObject.h"

Player::Player(char name, Grid::Square& square, int power, Direction direction) {
    this->direction = direction;
    this->name = name;
    this->power = power;
    pSquare = &square;
    square.stepIn(*this);
    remainingArrows = INITIAL_NUM_ARROWS;
    lastArrowTick = 0;
}

Player::~Player() {
    // Clear square before deletion
    stepOut();
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

    stepOut();
    square.stepIn(*this);
    pSquare = &square;
}

void Player::stepOut() const {
    // Notify square that player is leaving
    pSquare->stepOut(*this);
    pSquare->clear();
}

void Player::update(Game& game) {
    if (power > 0) {
        unsigned int tick = game.getTick();

        if (tick % MOVE_INTERVAL == 0) {
            // Move to next square
            setSquare(getNextMove(game));
        }

        if (
            remainingArrows &&                                  // Player still has arrows
            game.checkProbability(SHOOT_ARROW_PROBABILITY) &&   // Check probability, don't shoot on every chance
            tick > lastArrowTick + MIN_TICKS_BETWEEN_ARROWS &&  // Check minimum ticks between arrows
            hasPlayersInRange(game.getPlayers())                // Shoot only if there is a reasonable chance of hitting an opponent
        ) {
            // Shoot an arrow if conditions are met
            shootArrow(game);
        }
    }
}

Grid::Square& Player::getNextMove(const Game& game) {
    const Grid& grid = game.getGrid();

    // Find closest food / quiver
    DroppingObject* closest = findClosestObject(game.getDroppingObjects());
    if (closest && checkWallsInPath(grid, closest->getSquare())) {
        // Move towards the closest if it exists and the path is clear (no walls)
        direction = pSquare->getDirection(closest->getSquare());
    } else if (game.checkProbability(CHANGE_DIRECTION_PROBABILITY)) {
        // Randomly change direction
        setRandomDirection();
    }

    Grid::Square* nextSquare = &getNextSquare(grid, *pSquare, direction);
    while (nextSquare->hasWall()) {
        // Change direction to avoid the wall
        setRandomDirection();
        nextSquare = &getNextSquare(grid, *pSquare, direction);
    }

    return *nextSquare;
}

DroppingObject* Player::findClosestObject(const List& objects) const {
    DroppingObject* closest = NULL;
    if (!objects.isEmpty()) {
        double closestDistance = 0;
        List::Iterator it(objects);
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

bool Player::checkWallsInPath(const Grid& grid, const Grid::Square& target) const {
    bool result = true;
    Grid::Square* current = pSquare;
    while (result && current != &target) {
        // Simulate the actual movement and check for walls in the path
        Direction direction = current->getDirection(target);
        current = &getNextSquare(grid, *current, direction);
        if (current->hasWall()) {
            // Found a wall, no need to continue
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

void Player::shootArrow(Game& game) {
    Grid::Square& arrowSquare = getNextSquare(game.getGrid(), *pSquare, direction);
    if (!arrowSquare.hasWall()) {
        // Don't shoot directly at a wall
        Arrow* arrow = new Arrow(*this, arrowSquare);
        game.addArrow(*arrow); // Update game
        lastArrowTick = game.getTick();
        remainingArrows--;
    }
}

bool Player::hasPlayersInRange(const List& players) const {
    List::Iterator it(players);
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

void Player::addArrows(int amount) {
    remainingArrows += amount;
}

void Player::increasePower(int amount) {
    power = __max(power + amount, 0);
}

void Player::decreasePower(int amount) {
    increasePower(-amount);
}

const Grid::Square& Player::getSquare() const {
    return *pSquare;
}

char Player::getName() const {
    return name;
}

int Player::getPower() const {
    return power;
}

int Player::getRemainingArrows() const {
    return remainingArrows;
}

Direction Player::getDirection() const {
    return direction;
}

void Player::draw() const {
    pSquare->draw(name, CYAN);
}