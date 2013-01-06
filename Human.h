#ifndef _HUMAN_H
#define _HUMAN_H

#include "BasePlayer.h"

namespace HungerGames
{

    class Human: public BasePlayer
    {
        static int numInstances;

    public:
        Human(char name, Console::Color color);

        virtual void update();
    };

}

#endif