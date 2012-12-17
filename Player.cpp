#include "Player.h"
#include "Game.h"
#include "DroppingObject.h"
#include "RegularArrow.h"
#include "ExplodingArrow.h"
#include "PenetratingArrow.h"
#include <exception>

const int Player::INITIAL_POWER                   = 1000;
const int Player::MIN_TICKS_BETWEEN_ARROWS        = 3;
const int Player::SHOOT_ARROW_PROBABILITY         = 20;
const int Player::CHANGE_DIRECTION_PROBABILITY    = 10;
const int Player::MOVE_INTERVAL                   = 2;

Player::Player(char name) {
    this->name = name;
    power = INITIAL_POWER;
    direction = RIGHT;
    lastArrowTick = 0;
}

Player::~Player() {
    if (pGame->isRunning()) {
        // Clear square before deletion
        pSquare->stepOut(*this);
    }
}

void Player::setSquare(Grid::Square& square) {
    if (square.hasDroppingObject()) {
        // Pick up dropping object
        DroppingObject& droppingObject = square.getDroppingObject();
        droppingObject.affect(*this);
    }

    ObjectsList& players = square.getPlayers();
    if (!players.empty()) {
        // Fight other players on square
        ObjectsIterator it = players.begin();
        while (it != players.end()) {
            Player* player = (Player*) *it;
            fight(*player);
            it++;
        }
    }

    if (pSquare) {
        pSquare->stepOut(*this);
    }
    square.stepIn(*this);
    pSquare = &square;
}

bool Player::shootArrow(ArrowsBag::Type type) {
    Grid::Square& square = getNextSquare();
    if (
        arrowsBag.remaining[type] > 0 &&                            // Player still has arrows
        pGame->getTick() > lastArrowTick + MIN_TICKS_BETWEEN_ARROWS // Check minimum ticks between arrows
    ) {
        Arrow* arrow = arrowsBag.getArrow(type);
        arrow->setDirection(direction);
        pGame->addArrow(arrow, square); // Update game
        lastArrowTick = pGame->getTick();
        return true;
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
    pSquare->draw(name, Console::CYAN);
}

ostream& operator<<(ostream& out, const Player& player) {
    printf("%4d", player.power);
    return cout << player.arrowsBag;
}

// Player arrows bag

const int Player::ArrowsBag::INITIAL_NUM_REGULAR        = 2;
const int Player::ArrowsBag::INITIAL_NUM_EXPLODING      = 1;
const int Player::ArrowsBag::INITIAL_NUM_PENETRATING    = 1;

Player::ArrowsBag::ArrowsBag() {
    remaining[REGULAR] = INITIAL_NUM_REGULAR;
    remaining[EXPLODING] = INITIAL_NUM_EXPLODING;
    remaining[PENETRATING] = INITIAL_NUM_PENETRATING;
}

bool Player::ArrowsBag::isEmpty() const {
    return (remaining[REGULAR] + remaining[EXPLODING] + remaining[PENETRATING] == 0);
}

int Player::ArrowsBag::getRemaining(Type type) const {
    return remaining[type];
}

Player::ArrowsBag::Type Player::ArrowsBag::getAvailableRandomType() const {
    if (isEmpty()) {
        throw runtime_error("Arrows bag is empty");
    }

    // Check which arrow type is available
    int available[3], numAvailable = 0;
    for (int type = 0; type < 3; type++) {
        if (remaining[type] > 0) {
            available[numAvailable] = type;
            numAvailable++;
        }
    }

    // Choose randomly from available types
    int random = rand() % numAvailable;
    return (Type) available[random];
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

ostream& operator<<(ostream& out, const Player::ArrowsBag& arrowsBag) {
    printf(
        "%2d%2d%2d",
        arrowsBag.remaining[Player::ArrowsBag::REGULAR],
        arrowsBag.remaining[Player::ArrowsBag::EXPLODING],
        arrowsBag.remaining[Player::ArrowsBag::PENETRATING]
    );
    return out;
}