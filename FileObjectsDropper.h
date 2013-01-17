#ifndef _FILE_OBJECTS_DROPPER_H
#define _FILE_OBJECTS_DROPPER_H

#include "ObjectsDropper.h"
#include "EventsFile.h"

namespace HungerGames
{

    class FileObjectsDropper: public ObjectsDropper
    {
        static const Action DROP_FOOD;
        static const Action DROP_QUIVER;
        static const Action DROP_BOMB;

        EventsFile events;

    public:
        FileObjectsDropper(const char* filename);

        virtual void drop(Game& game);
    };

}

#endif