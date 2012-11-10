#ifndef _GAME_H
#define _GAME_H

#include "Grid.h"
#include "Object.h"
#include "InfoBox.h"
#include <list>

const int FRAMES_PER_SECOND = 30;
const int DROP_FOOD_PROBABILITY = 2;
const int DROP_QUIVER_PROBABILITY = 1;
const int DROP_BOMB_PROBABILITY = 1;

typedef std::list<Object*> ObjectsList;
typedef ObjectsList::iterator ObjectsIterator;

bool checkProbability(int probability);

class Game
{
    int fps;
    int tick;
    bool paused;
    Grid grid;
    ObjectsList objects;
    PlayersList players;
    InfoBox infoBox;

    void Loop();
    void Update();
    void CheckCollisions();
    void DropObjects();
    void DropObject(DroppingObject* object);
    bool IsValidSquare(Square* square);
    void Draw();

public:
    Game();
    ~Game();

    void AddPlayer(int row, int col);
    void AddWall(int row, int col);
    void AddInfoBox(int row, int col);
    void AddObject(Object* object, int row, int col);
    void AddObject(Object* object, Square* square);
    void RemoveObject(Object* object);
    void RemovePlayer(Player* player);
    int GetTick();
    Grid* GetGrid();
    PlayersList* GetPlayers();

    void Run();
    void Pause();
};

#endif