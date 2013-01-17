#ifndef _SCHEDULED_PLAYER_H
#define _SCHEDULED_PLAYER_H

#include "BasePlayer.h"
#include "EventsFile.h"

namespace HungerGames
{

    class ScheduledPlayer: public BasePlayer
    {
        EventsFile events;

    public:
        ScheduledPlayer(char name, Console::Color color, const char* eventsFilename);

        virtual void update();
    };

}

#endif