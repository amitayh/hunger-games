#ifndef _MAP_LOADER_H
#define _MAP_LOADER_H

#include "Console.h"
#include <string>

class Game;

class MapLoader
{
    static const char CHAR_WALL         = 'W';
    static const char CHAR_BOT          = 'P';
    static const char CHAR_HUMAN        = 'H';
    static const char CHAR_INFO_BOX     = 'O';
    static const int MIN_NUM_PLAYERS    = 2;
    static const int MAX_NUM_PLAYERS    = 3;
    static const Console::Color PLAYER_COLORS[3];

    Game* pGame;

    Console::Color getPlayerColor() const;

public:
    MapLoader(Game& game);

    bool load(const std::string& filename) const;
};

#endif