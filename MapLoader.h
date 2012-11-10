#ifndef _MAP_LOADER_H
#define _MAP_LOADER_H

#include "Game.h"

const char CHAR_WALL        = 'W';
const char CHAR_PLAYER      = 'P';
const char CHAR_INFO_BOX    = 'O';

class MapLoader
{
    Game* game;
public:
    MapLoader(Game* game);

    bool Load(const char* filename);
};

#endif