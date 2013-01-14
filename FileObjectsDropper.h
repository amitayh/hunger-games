#ifndef _FILE_OBJECTS_DROPPER_H
#define _FILE_OBJECTS_DROPPER_H

#include "ObjectsDropper.h"
#include "EventsFile.h"

namespace HungerGames
{

    class FileObjectsDropper: public ObjectsDropper
    {
        static const char FOOD_ACTION;
        static const char QUIVER_ACTION;
        static const char BOMB_ACTION;

        EventsFile events;

    public:
        FileObjectsDropper(const char* filename);

        virtual void drop(Game& game);
    };

}

#endif