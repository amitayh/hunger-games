#ifndef _MAP_LOADER_H
#define _MAP_LOADER_H

#include "Game.h"

class MapLoader
{
    enum {
        CHAR_WALL       = 'W',
        CHAR_BOT        = 'P',
        CHAR_HUMAN      = 'H',
        CHAR_INFO_BOX   = 'O',
        MIN_NUM_PLAYERS = 2,
        MAX_NUM_PLAYERS = 3
    };

    Game* pGame;

public:
    MapLoader(Game& game);

    bool load(const string& filename) const;
};

#endif