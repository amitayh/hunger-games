#ifndef _QUIVER_H
#define _QUIVER_H

#include "DroppingObject.h"

class Quiver: public DroppingObject
{
public:
    Quiver();

    void affect(BasePlayer& player);

    void draw() const;
};

#endif