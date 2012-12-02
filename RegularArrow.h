#ifndef _REGULAR_ARROW_H
#define _REGULAR_ARROW_H

#include "Arrow.h"

class RegularArrow : public Arrow
{
public:
    RegularArrow(Player& shooter);

protected:
    bool checkHit();
};

#endif