#ifndef _HUMAN_PLAYER_H
#define _HUMAN_PLAYER_H

#include "BasePlayer.h"

namespace HungerGames
{

    class HumanPlayer: public BasePlayer
    {
        static int numInstances;

    public:
        HumanPlayer(char name, Console::Color color);

        virtual void update();
    };

}

#endif