#ifndef _SQUARE_H
#define _SQUARE_H

#include <list>

class Player;
class Arrow;
class DroppingObject;
class Wall;

typedef std::list<Player*> PlayersList;
typedef PlayersList::iterator PlayersListIterator;
typedef std::list<Arrow*> ArrowsList;
typedef ArrowsList::iterator ArrowsListIterator;

class Square
{
    int row, col;
	PlayersList players;
	ArrowsList arrows;
	DroppingObject* droppingObject;
	Wall* wall;
public:
	Square();

    void Enter(Player* player);
    void Leave(Player* player);
	void Enter(Arrow* arrow);
    void Leave(Arrow* arrow);
    void SetPosition(int row, int col);
	bool SetDroppingObject(DroppingObject* droppingObject);
	void SetWall(Wall* wall);
    int GetRow();
    int GetCol();
    PlayersList* GetPlayers();
    DroppingObject* GetDroppingObject();
    Wall* GetWall();
};

#endif