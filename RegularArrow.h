#ifndef _REGULAR_ARROW_H
#define _REGULAR_ARROW_H

#include "BaseArrow.h"

namespace HungerGames
{

    class RegularArrow: public BaseArrow
    {
    public:
        virtual void draw() const;

    protected:
        virtual bool checkHit();
    };

}

#endif