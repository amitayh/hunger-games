#ifndef _BASE_PLAYER_H
#define _BASE_PLAYER_H

#include "MovingObject.h"
#include "EventsFile.h"
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
            static const int INITIAL_NUM_REGULAR;
            static const int INITIAL_NUM_EXPLODING;
            static const int INITIAL_NUM_PENETRATING;
            enum Type {
                REGULAR,
                EXPLODING,
                PENETRATING,
                NONE
            };
            ArrowsBag();
            BaseArrow& getArrow(Type type);
            bool isEmpty() const;
            int getRemaining(Type type) const;
            Type getAvailableRandomType() const;
            ArrowsBag& operator+=(int amount);
            ArrowsBag& operator++();
            friend class BasePlayer;
        };

        ~BasePlayer();

        virtual void update();
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
        static const int INITIAL_POWER;
        static const int MIN_TICKS_BETWEEN_ARROWS;
        static const int MOVE_INTERVAL;
        static const Action MOVE_LEFT;
        static const Action MOVE_RIGHT;
        static const Action MOVE_UP;
        static const Action MOVE_DOWN;
        static const Action SHOOT_REGULAR_ARROW;
        static const Action SHOOT_EXPLODING_ARROW;
        static const Action SHOOT_PENETRATING_ARROW;

        BasePlayer(char name, Console::Color color); // Make class abstract

        Console::Color color;
        char name;
        int power;
        ArrowsBag arrowsBag;
        unsigned int lastArrowTick;
        ArrowsBag::Type nextArrowType;

        void fight(BasePlayer& opponent);
        bool shootArrow(ArrowsBag::Type type);
        void doAction(Action action);
    };

}

// Overloading cout's << operator - must be in global namespace
ostream& operator<<(ostream& out, const BasePlayer& player);
ostream& operator<<(ostream& out, const BasePlayer::ArrowsBag& arrowsBag);

#endif