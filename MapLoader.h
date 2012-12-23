#ifndef _MAP_LOADER_H
#define _MAP_LOADER_H

#include "Console.h"
#include <string>

namespace HungerGames
{

    class Game;

    class MapLoader
    {
        static const char CHAR_WALL;
        static const char CHAR_BOT;
        static const char CHAR_HUMAN;
        static const char CHAR_INFO_BOX;
        static const int MIN_NUM_PLAYERS;
        static const int MAX_NUM_PLAYERS;
        static const Console::Color PLAYER_COLORS[];

        Game* pGame;

        Console::Color getPlayerColor() const;

    public:
        MapLoader(Game& game);

        bool load(const std::string& filename) const;
    };

}

#endif