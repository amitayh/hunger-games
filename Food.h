#ifndef _FOOD_H
#define _FOOD_H

#include "DroppingObject.h"

namespace HungerGames
{

    class Food: public DroppingObject
    {
    public:
        Food();

        virtual void affect(BasePlayer& player);

        virtual void draw() const;
    };

}

#endif