#ifndef _BASE_OBJECT_H
#define _BASE_OBJECT_H

#include "Grid.h"

namespace HungerGames
{

    class Game;

    class BaseObject
    {
    public:
        struct Draw {
            void operator()(BaseObject* object) const;
        };

        struct Delete {
            void operator()(BaseObject* object) const;
        };

        BaseObject();
        virtual ~BaseObject() {};

        void setGame(Game& game);
        virtual void setSquare(Grid::Square& square);
    
        virtual void draw() const = 0;
        Grid::Square& getSquare() const;

    protected:
        Game* pGame;
        Grid::Square *pSquare;
    };

}

#endif