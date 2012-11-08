#ifndef _SQUARE_H
#define _SQUARE_H

#include <list>

class Player;
class DroppingObject;
class Wall;

typedef std::list<Player*> PlayersList;
typedef PlayersList::iterator PlayersIterator;

class Square
{
    int row, col;
	PlayersList players;
	DroppingObject* droppingObject;
	Wall* wall;
public:
	Square();

    void StepIn(Player* player);
    void StepOut(Player* player);
    void SetPosition(int row, int col);
	void SetDroppingObject(DroppingObject* droppingObject);
	void SetWall(Wall* wall);
    int GetRow();
    int GetCol();
    PlayersList* GetPlayers();
    DroppingObject* GetDroppingObject();
    Wall* GetWall();
	bool IsEmpty();
};

#endif