#ifndef _EXPLODING_ARROW_H
#define _EXPLODING_ARROW_H

#include "BaseArrow.h"

namespace HungerGames
{

    class ExplodingArrow: public BaseArrow
    {
    public:
        virtual void draw() const;

    protected:
        virtual bool checkHit();
    };

}

#endif