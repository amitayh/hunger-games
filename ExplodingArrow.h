#ifndef _EXPLODING_ARROW_H
#define _EXPLODING_ARROW_H

#include "Arrow.h"

class ExplodingArrow: public Arrow
{
public:
    void draw() const;

protected:
    bool checkHit();
};

#endif