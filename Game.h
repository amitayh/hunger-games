#ifndef _GAME_H
#define _GAME_H

#include "Grid.h"
#include "Object.h"
#include <list>

const int FRAMES_PER_SECOND = 15;

typedef std::list<Object*> ObjectsList;
typedef ObjectsList::iterator ObjectsIterator;

class Game
{
	int fps;
    int tick;
    bool paused;
	Grid grid;
	ObjectsList objects;

	void Loop();
	void Update();
	void CheckCollisions();
	void DropObjects();
	void DropObject(DroppingObject* object);
	void Draw();

public:
	Game();
    ~Game();

	void AddObject(Object* object, int row, int col);
	void AddObject(Object* object, Square* square);
    void RemoveObject(Object* object);
	int GetTick();
	Grid* GetGrid();

    void Run();
    void Pause();
};

#endif