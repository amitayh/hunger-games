#ifndef _BASE_PLAYER_H
#define _BASE_PLAYER_H

#include "MovingObject.h"
#include <ostream>

using namespace std;

class BaseArrow;

class BasePlayer: public MovingObject
{
public:
    class ArrowsBag
    {
        int remaining[3];
    public:
        static const int INITIAL_NUM_REGULAR;
        static const int INITIAL_NUM_EXPLODING;
        static const int INITIAL_NUM_PENETRATING;
        enum Type {
            REGULAR,
            EXPLODING,
            PENETRATING
        };
        ArrowsBag();
        BaseArrow* getArrow(Type type);
        bool isEmpty() const;
        int getRemaining(Type type) const;
        Type getAvailableRandomType() const;
        ArrowsBag& operator+=(int amount);
        ArrowsBag& operator++();
        friend ostream& operator<<(ostream& out, const ArrowsBag& arrowsBag);
        friend class BasePlayer;
    };

    ~BasePlayer();

    virtual void setSquare(Grid::Square& square);
    void setColor(Console::Color color);
    void increasePower(int amount);
    void decreasePower(int amount);
    ArrowsBag& getArrowsBag();

    Console::Color getColor() const;
    char getName() const;
    int getPower() const;
    virtual void draw() const;

    friend ostream& operator<<(ostream& out, const BasePlayer& player);

protected:
    static const int INITIAL_POWER;
    static const int MIN_TICKS_BETWEEN_ARROWS;
    static const int SHOOT_ARROW_PROBABILITY;
    static const int CHANGE_DIRECTION_PROBABILITY;
    static const int MOVE_INTERVAL;

    BasePlayer(char name); // Make class abstract

    Console::Color color;
    char name;
    int power;
    ArrowsBag arrowsBag;
    unsigned int lastArrowTick;

    void fight(BasePlayer& opponent);
    bool shootArrow(ArrowsBag::Type type);
};

#endif