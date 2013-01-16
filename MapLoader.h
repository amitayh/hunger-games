#ifndef _MAP_LOADER_H
#define _MAP_LOADER_H

#include "Console.h"
#include <stdio.h>

namespace HungerGames
{

    class Game;

    class MapLoader
    {
        static const char CHAR_WALL;
        static const char CHAR_BOT;
        static const char CHAR_HUMAN_PLAYER;
        static const char CHAR_SCHEDULED_PLAYER;
        static const char CHAR_INFO_BOX;
        static const char CHAR_EVENTS_FILE;
        static const char FILE_SEPARATOR;
        static const char FIRST_PLAYER_NAME;
        static const int MIN_NUM_PLAYERS;
        static const int MAX_NUM_PLAYERS;
        static const int MIN_ARG_LENGTH;
        static const int NUM_COLORS = 3;
        static const Console::Color PLAYER_COLORS[NUM_COLORS];

        Game* pGame;

        Console::Color getPlayerColor() const;

    public:
        MapLoader(Game& game);

        void loadFromArguments(int argc, char* argv[]) const;
        void load(const char* mapFile, const char* eventsFile = NULL, char* scheduledPlayersFiles[] = NULL) const;
    };

}

#endif