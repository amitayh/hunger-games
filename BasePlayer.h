#ifndef _BASE_PLAYER_H
#define _BASE_PLAYER_H

#include "MovingObject.h"
#include <ostream>

using namespace std;
using namespace HungerGames;

namespace HungerGames
{

    class BaseArrow;

    class BasePlayer: public MovingObject
    {
    public:
        class ArrowsBag
        {
            int remaining[3];
        public:
            static const int INITIAL_NUM_REGULAR        = 2;
            static const int INITIAL_NUM_EXPLODING      = 1;
            static const int INITIAL_NUM_PENETRATING    = 1;
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
            friend class BasePlayer;
        };

        ~BasePlayer();

        virtual void setSquare(Grid::Square& square);
        void increasePower(int amount);
        void decreasePower(int amount);
        ArrowsBag& getArrowsBag();

        Console::Color getColor() const;
        char getName() const;
        int getPower() const;
        bool isAlive() const;
        const ArrowsBag& getArrowsBag() const;
        virtual void draw() const;

    protected:
        static const int INITIAL_POWER                  = 1000;
        static const int MIN_TICKS_BETWEEN_ARROWS       = 3;
        static const int SHOOT_ARROW_PROBABILITY        = 20;
        static const int CHANGE_DIRECTION_PROBABILITY   = 10;
        static const int MOVE_INTERVAL                  = 2;

        BasePlayer(char name, Console::Color color); // Make class abstract

        Console::Color color;
        char name;
        int power;
        ArrowsBag arrowsBag;
        unsigned int lastArrowTick;

        void fight(BasePlayer& opponent);
        bool shootArrow(ArrowsBag::Type type);
    };

}

// Overloading cout's << operator - must be in global namespace
ostream& operator<<(ostream& out, const BasePlayer& player);
ostream& operator<<(ostream& out, const BasePlayer::ArrowsBag& arrowsBag);

#endif