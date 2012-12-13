#ifndef _MAP_LOADER_H
#define _MAP_LOADER_H

#include "Game.h"

class MapLoader
{
    static const char CHAR_WALL;
    static const char CHAR_BOT;
    static const char CHAR_HUMAN;
    static const char CHAR_INFO_BOX;
    static const int MIN_NUM_PLAYERS;
    static const int MAX_NUM_PLAYERS;

    Game* pGame;

public:
    MapLoader(Game& game);

    bool load(const string& filename) const;
};

#endif