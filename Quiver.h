#ifndef _QUIVER_H
#define _QUIVER_H

#include "DroppingObject.h"

namespace HungerGames
{

    class Quiver: public DroppingObject
    {
    public:
        Quiver();

        virtual void affect(BasePlayer& player);

        virtual void draw() const;
    };

}

#endif