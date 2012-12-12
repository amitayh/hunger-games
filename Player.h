#ifndef _PLAYER_H
#define _PLAYER_H

#include "MovingObject.h"
#include <ostream>

using namespace std;

class Arrow;

class Player: public MovingObject
{
public:
    class ArrowsBag
    {
        int remaining[3];
    public:
        enum {
            INITIAL_NUM_REGULAR     = 2,
            INITIAL_NUM_EXPLODING   = 1,
            INITIAL_NUM_PENETRATING = 1,
        };
        enum Type {
            REGULAR,
            EXPLODING,
            PENETRATING
        };
        ArrowsBag();
        Arrow* getArrow(Type type);
        bool isEmpty() const;
        int getRemaining(Type type) const;
        Type getAvailableRandomType() const;
        ArrowsBag& operator+=(int amount);
        ArrowsBag& operator++();
        friend ostream& operator<<(ostream& out, const ArrowsBag& arrowsBag);
        friend class Player;
    };

    ~Player();

    void setSquare(Grid::Square& square);
    void increasePower(int amount);
    void decreasePower(int amount);
    ArrowsBag& getArrowsBag();

    char getName() const;
    int getPower() const;
    void draw() const;

    friend ostream& operator<<(ostream& out, const Player& player);

protected:
    enum {
        INITIAL_POWER                   = 1000,
        MIN_TICKS_BETWEEN_ARROWS        = 3,
        SHOOT_ARROW_PROBABILITY         = 20,
        CHANGE_DIRECTION_PROBABILITY    = 10,
        MOVE_INTERVAL                   = 2
    };

    Player(char name); // Make class abstract

    char name;
    int power;
    ArrowsBag arrowsBag;
    unsigned int lastArrowTick;

    void fight(Player& opponent);
    void shootArrow(ArrowsBag::Type type);
};

#endif