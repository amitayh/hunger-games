#ifndef _REGULAR_ARROW_H
#define _REGULAR_ARROW_H

#include "Arrow.h"

class RegularArrow: public Arrow
{
public:
    void draw() const;

protected:
    bool checkHit();
};

#endif