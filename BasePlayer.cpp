#include "BasePlayer.h"
#include "Game.h"
#include "DroppingObject.h"
#include "RegularArrow.h"
#include "ExplodingArrow.h"
#include "PenetratingArrow.h"
#include <iostream>
#include <exception>

using namespace std;
using namespace HungerGames;

const int   BasePlayer::INITIAL_POWER                   = 1000;
const int   BasePlayer::MIN_TICKS_BETWEEN_ARROWS        = 3;
const int   BasePlayer::MOVE_INTERVAL                   = 2;
const char  BasePlayer::ACTION_LEFT                     = 'a';
const char  BasePlayer::ACTION_RIGHT                    = 'd';
const char  BasePlayer::ACTION_UP                       = 'w';
const char  BasePlayer::ACTION_DOWN                     = 's';
const char  BasePlayer::ACTION_SHOOT_REGULAR_ARROW      = 'p';
const char  BasePlayer::ACTION_SHOOT_EXPLODING_ARROW    = 'i';
const char  BasePlayer::ACTION_SHOOT_PENETRATING_ARROW  = 'o';

BasePlayer::BasePlayer(char name, Console::Color color) {
    this->name = name;
    this->color = color;
    power = INITIAL_POWER;
    direction = RIGHT;
    lastArrowTick = 0;
    nextArrowType = ArrowsBag::NONE;
}

BasePlayer::~BasePlayer() {
    if (pGame && pGame->isRunning()) {
        // Clear square before deletion
        pSquare->stepOut(*this);
    }
}

void BasePlayer::update() {
    if (power > 0) {
        if (pGame->getTick() % MOVE_INTERVAL == 0) {
            setSquare(getNextSquare());
        }
        if (nextArrowType != ArrowsBag::NONE) {
            shootArrow(nextArrowType);
        }
    }
}

void BasePlayer::setSquare(Grid::Square& square) {
    if (!square.hasWall()) {
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
                BasePlayer* player = (BasePlayer*) *it;
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
}

bool BasePlayer::shootArrow(ArrowsBag::Type type) {
    Grid::Square& square = getNextSquare();
    if (
        arrowsBag.remaining[type] > 0 &&                            // Player still has arrows
        pGame->getTick() > lastArrowTick + MIN_TICKS_BETWEEN_ARROWS // Check minimum ticks between arrows
    ) {
        BaseArrow* arrow = arrowsBag.getArrow(type);
        arrow->setDirection(direction);
        pGame->addArrow(arrow, square); // Update game
        lastArrowTick = pGame->getTick();
        return true;
    }
    return false;
}

void BasePlayer::fight(BasePlayer& opponent) {
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

void BasePlayer::doAction(char action) {
    switch (action) {
        case ACTION_LEFT:
            direction = LEFT;
            break;
        case ACTION_RIGHT:
            direction = RIGHT;
            break;
        case ACTION_UP:
            direction = UP;
            break;
        case ACTION_DOWN:
            direction = DOWN;
            break;
        case ACTION_SHOOT_REGULAR_ARROW:
            nextArrowType = ArrowsBag::REGULAR;
            break;
        case ACTION_SHOOT_EXPLODING_ARROW:
            nextArrowType = ArrowsBag::EXPLODING;
            break;
        case ACTION_SHOOT_PENETRATING_ARROW:
            nextArrowType = ArrowsBag::PENETRATING;
            break;
    }
}

void BasePlayer::increasePower(int amount) {
    power = __max(power + amount, 0);
}

void BasePlayer::decreasePower(int amount) {
    increasePower(-amount);
}

Console::Color BasePlayer::getColor() const {
    return color;
}

char BasePlayer::getName() const {
    return name;
}

int BasePlayer::getPower() const {
    return power;
}

bool BasePlayer::isAlive() const {
    return power > 0;
}

BasePlayer::ArrowsBag& BasePlayer::getArrowsBag() {
    return arrowsBag;
}

const BasePlayer::ArrowsBag& BasePlayer::getArrowsBag() const {
    return arrowsBag;
}

void BasePlayer::draw() const {
    pSquare->draw(name, color);
}

ostream& operator<<(ostream& out, const BasePlayer& player) {
    Console::changeColor(player.getColor());
    printf("%4d", player.getPower());
    return cout << player.getArrowsBag();
}

// Player arrows bag

const int BasePlayer::ArrowsBag::INITIAL_NUM_REGULAR        = 2;
const int BasePlayer::ArrowsBag::INITIAL_NUM_EXPLODING      = 1;
const int BasePlayer::ArrowsBag::INITIAL_NUM_PENETRATING    = 1;

BasePlayer::ArrowsBag::ArrowsBag() {
    remaining[REGULAR] = INITIAL_NUM_REGULAR;
    remaining[EXPLODING] = INITIAL_NUM_EXPLODING;
    remaining[PENETRATING] = INITIAL_NUM_PENETRATING;
}

bool BasePlayer::ArrowsBag::isEmpty() const {
    return (remaining[REGULAR] + remaining[EXPLODING] + remaining[PENETRATING] == 0);
}

int BasePlayer::ArrowsBag::getRemaining(Type type) const {
    return remaining[type];
}

BasePlayer::ArrowsBag::Type BasePlayer::ArrowsBag::getAvailableRandomType() const {
    if (isEmpty()) {
        throw logic_error("Arrows bag is empty");
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

BaseArrow* BasePlayer::ArrowsBag::getArrow(Type type) {
    BaseArrow* arrow = NULL;
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

BasePlayer::ArrowsBag& BasePlayer::ArrowsBag::operator+=(int amount) {
    remaining[REGULAR] += amount;
    remaining[EXPLODING] += amount;
    remaining[PENETRATING] += amount;
    return *this;
}

BasePlayer::ArrowsBag& BasePlayer::ArrowsBag::operator++() {
    // Add one arrow of each type
    return (*this += 1);
}

ostream& operator<<(ostream& out, const BasePlayer::ArrowsBag& arrowsBag) {
    printf(
        "%2d%2d%2d",
        arrowsBag.getRemaining(BasePlayer::ArrowsBag::REGULAR),
        arrowsBag.getRemaining(BasePlayer::ArrowsBag::EXPLODING),
        arrowsBag.getRemaining(BasePlayer::ArrowsBag::PENETRATING)
    );
    return out;
}