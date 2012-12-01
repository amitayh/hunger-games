#ifndef _QUIVER_H
#define _QUIVER_H

#include "DroppingObject.h"

class Quiver : public DroppingObject
{
public:
    void affect(Player& player);

    void draw() const;
};

#endif