#ifndef _PLAYER_H
#define _PLAYER_H

#include "MovingObject.h"

class Game;

class Player : public MovingObject
{
    enum {
        INITIAL_POWER                   = 1000,
        INITIAL_NUM_ARROWS              = 4,
        MIN_TICKS_BETWEEN_ARROWS        = 3,
        SHOOT_ARROW_PROBABILITY         = 20,
        CHANGE_DIRECTION_PROBABILITY    = 10,
        MOVE_INTERVAL                   = 2
    };

    Grid::Square* pSquare;
    MovingObject::Direction direction;
    char name;
    int power;
    int remainingArrows;
    unsigned int lastArrowTick;

    void setSquare(Grid::Square& square);
    void fight(Player& opponent);
    void setRandomDirection();
    void shootArrow(Game& game);
    Grid::Square& getNextMove(const Game& game);

    DroppingObject* findClosestObject(const List& objects) const;
    bool checkWallsInPath(const Grid& grid, const Grid::Square& target) const;
    bool hasPlayersInRange(const List& players) const;
    bool playerInRange(const Player& opponent) const;
    void stepOut() const;

public:
    Player(char name, Grid::Square& square, int power = INITIAL_POWER, MovingObject::Direction direction = MovingObject::Direction::RIGHT);
    ~Player();

    void update(Game& game);
    void increasePower(int amount);
    void decreasePower(int amount);
    void addArrows(int amount);

    char getName() const;
    int getPower() const;
    int getRemainingArrows() const;
    const Grid::Square& getSquare() const;
    void draw() const;
};

#endif