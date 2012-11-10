#ifndef _ITEM_H
#define _ITEM_H

#include "Object.h"

enum ItemType {
    FOOD,
    QUIVER,
    BOMB
};

class Item : public Object
{
    ItemType type;
};

#endif