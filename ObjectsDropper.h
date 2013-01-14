#ifndef _OBJECTS_DROPPER_H
#define _OBJECTS_DROPPER_H

namespace HungerGames
{

    class Game;

    class ObjectsDropper
    {
    public:
        virtual ~ObjectsDropper() {};

        virtual void drop(Game& game) = 0;
    };

}

#endif