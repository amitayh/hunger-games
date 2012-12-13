#ifndef _REGULAR_ARROW_H
#define _REGULAR_ARROW_H

#include "Arrow.h"

class RegularArrow: public Arrow
{
public:
    virtual void draw() const;

protected:
    virtual bool checkHit();
};

#endif