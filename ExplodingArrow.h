#ifndef _EXPLODING_ARROW_H
#define _EXPLODING_ARROW_H

#include "Arrow.h"

class ExplodingArrow: public Arrow
{
public:
    virtual void draw() const;

protected:
    virtual bool checkHit();
};

#endif