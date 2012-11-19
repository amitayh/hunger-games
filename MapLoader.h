#ifndef _MAP_LOADER_H
#define _MAP_LOADER_H

#include "Game.h"

class MapLoader
{
    enum {
        CHAR_WALL       = 'W',
        CHAR_PLAYER     = 'P',
        CHAR_INFO_BOX   = 'O',
        MIN_NUM_PLAYERS = 2
    };

    Game *game;

public:
    MapLoader(Game *game);

    bool Load(const char *filename);
};

#endif