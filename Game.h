#ifndef _GAME_H
#define _GAME_H

#include "Grid.h"
#include "Player.h"
#include "Wall.h"
#include "Arrow.h"
#include <list>

const int FRAMES_PER_SECOND = 10;

typedef std::list<Wall*> WallsList;
typedef std::list<Player*> PlayersList;
typedef std::list<Arrow*> ArrowsList;

class Game
{
	int fps;
    int tick;
    bool paused;
	Grid grid;
	WallsList walls;
    PlayersList players;
    ArrowsList arrows;

public:
	Game();
    ~Game();

    void Run();
    void Pause();

    void Add(Player* player, int row, int col);
    void Add(Wall* wall, int row, int col);
    void Add(Arrow* arrow);

    void Remove(Arrow* arrow);

	void Loop();
	void Update();
    void CheckCollisions();
	void Draw();

    int GetTick();
	Grid* GetGrid();
};

#endif