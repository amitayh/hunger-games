#ifndef _MAP_LOADER_H
#define _MAP_LOADER_H

#include "Game.h"

class MapLoader
{
    Game* game;

public:
    static const char CHAR_WALL;
    static const char CHAR_PLAYER;
    static const char CHAR_INFO_BOX;
    static const int  MIN_NUM_PLAYERS;

    MapLoader(Game* game);

    bool Load(const char* filename);
};

#endif