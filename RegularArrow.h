#ifndef _REGULAR_ARROW_H
#define _REGULAR_ARROW_H

#include "Arrow.h"

class RegularArrow : public Arrow
{
public:
    RegularArrow();

protected:
    bool checkHit();
};

#endif