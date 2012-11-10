#ifndef _SQUARE_H
#define _SQUARE_H

#include <list>

class Player;
class Item;
class Wall;

typedef std::list<Player*> PlayersList;
typedef PlayersList::iterator PlayersIterator;

class Square
{
    int row, col;
    PlayersList players;
    Item* item;
    Wall* wall;
public:
    Square();

    void StepIn(Player* player);
    void StepOut(Player* player);
    void SetPosition(int row, int col);
    void SetItem(Item* item);
    void SetWall(Wall* wall);
    int GetRow();
    int GetCol();
    PlayersList* GetPlayers();
    Item* GetItem();
    Wall* GetWall();
    bool IsEmpty();
};

#endif