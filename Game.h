#ifndef _GAME_H
#define _GAME_H

#include "Grid.h"
#include "Arrow.h"
#include "InfoBox.h"
#include <list>

const int FRAMES_PER_SECOND = 20;
const int DROP_FOOD_PROBABILITY = 2;
const int DROP_QUIVER_PROBABILITY = 1;
const int DROP_BOMB_PROBABILITY = 1;

typedef std::list<Wall*> WallsList;
typedef WallsList::iterator WallsIterator;

typedef std::list<Arrow*> ArrowsList;
typedef ArrowsList::iterator ArrowsIterator;

typedef std::list<DroppingObject*> DroppingObjectsList;
typedef DroppingObjectsList::iterator DroppingObjectsIterator;

class Game
{
    int fps;
    unsigned int tick;
    bool paused;
    Grid grid;
    WallsList walls;
    PlayersList players;
    ArrowsList arrows;
    DroppingObjectsList droppingObjects;
    InfoBox infoBox;

    void Loop();
    void Update();
    void UpdatePlayers();
    void UpdateArrows();
    void DrawDroppingObjects();
    void DrawWalls();
    //void CheckCollisions();
    void DropObjects();
    void DropObject(DroppingObject* object);
    bool IsValidSquare(Square* square);
    //void Draw();

public:
    Game();
    ~Game();

    void AddPlayer(int row, int col);
    void AddWall(int row, int col);
    void AddInfoBox(int row, int col);
    void AddArrow(Arrow* arrow);
    void AddObject(Object* object, int row, int col);
    void AddObject(Object* object, Square* square);
    bool CheckProbability(int probability);
    int GetTick();
    Grid* GetGrid();
    PlayersList* GetPlayers();

    void Run();
    void Pause();
    void Resume();
};

#endif