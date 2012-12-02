#ifndef _PLAYER_H
#define _PLAYER_H

#include "MovingObject.h"

class Arrow;

class Player : public MovingObject
{
public:
    class ArrowsBag
    {
        int remaining[3];
    public:
        enum Type {
            REGULAR,
            EXPLODING,
            PENETRATING
        };
        bool isEmpty() const;
        int getRemaining(Type type) const;
        Arrow* getArrow();
        ArrowsBag& operator++();
        friend class Player;
    };

private:
    enum {
        INITIAL_POWER                   = 1000,
        INITIAL_NUM_REGULAR_ARROWS      = 2,
        INITIAL_NUM_EXPLODING_ARROWS    = 1,
        INITIAL_NUM_PENETRATING_ARROWS  = 1,
        MIN_TICKS_BETWEEN_ARROWS        = 3,
        SHOOT_ARROW_PROBABILITY         = 20,
        CHANGE_DIRECTION_PROBABILITY    = 10,
        MOVE_INTERVAL                   = 2
    };

    char name;
    int power;
    ArrowsBag arrowsBag;
    unsigned int lastArrowTick;

    void fight(Player& opponent);
    void setRandomDirection();
    void shootArrow();
    Grid::Square& getNextMove();

    DroppingObject* findClosestObject() const;
    bool isClearPath(const Grid::Square& target) const;
    bool hasPlayersInRange() const;
    bool playerInRange(const Player& opponent) const;

public:
    Player(char name, int power = INITIAL_POWER, Direction direction = RIGHT);
    ~Player();

    void setSquare(Grid::Square& square);
    void update();
    void increasePower(int amount);
    void decreasePower(int amount);
    ArrowsBag& getArrowsBag();

    char getName() const;
    int getPower() const;
    void draw() const;
};

#endif