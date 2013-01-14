#ifndef _RANDOM_OBJECTS_DROPPER_H
#define _RANDOM_OBJECTS_DROPPER_H

#include "ObjectsDropper.h"

namespace HungerGames
{

    class RandomObjectsDropper: public ObjectsDropper
    {
        static const int FOOD_PROBABILITY;
        static const int QUIVER_PROBABILITY;
        static const int BOMB_PROBABILITY;

    public:
        virtual void drop(Game& game);
    };

}

#endif