#ifndef _BOMB_H
#define _BOMB_H

#include "DroppingObject.h"

namespace HungerGames
{

    class Bomb: public DroppingObject
    {
    public:
        Bomb();

        virtual void affect(BasePlayer& player);

        virtual void draw() const;
    };

}

#endif