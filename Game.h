#ifndef _GAME_H
#define _GAME_H

#include "Grid.h"
#include "Arrow.h"
#include "InfoBox.h"
#include "Menu.h"
#include "DroppingObject.h"
#include "Gotoxy.h"
#include <iostream>

using namespace std;

const int ESCAPSE_KEY = 27;

class Game
{
    enum {
        FRAMES_PER_SECOND           = 25,
        DROP_FOOD_PROBABILITY       = 2,
        DROP_QUIVER_PROBABILITY     = 2,
        DROP_BOMB_PROBABILITY       = 1,
        MIN_DISTANCE_FROM_PLAYERS   = 2,
        MENU_RESUME                 = 1,
        MENU_QUIT                   = 2
    };

    unsigned int tick;
    bool running;
    Grid grid;
    List walls;
    List players;
    List arrows;
    List droppingObjects;
    InfoBox infoBox;
    Menu menu;

    void Loop();
    bool Update();
    void Draw();
    void UpdatePlayers();
    void DrawPlayers();
    void UpdateArrows();
    void DrawArrows();
    void UpdateDroppingObjects();
    void DrawDroppingObjects();
    void DrawWalls();
    void DropObjects();
    void DropObject(DroppingObject::Type type);
    void EndGame(const Player *winner = NULL);
    bool IsValidDrop(Square &square);
    void ShowMenu();

public:
    Game();
    ~Game();

    void AddPlayer(int row, int col);
    void AddPlayer(Square &square);
    void AddWall(int row, int col);
    void AddInfoBox(int row, int col);
    void AddArrow(Arrow &arrow);
    bool CheckProbability(int probability) const;
    unsigned int GetTick() const;
    List &GetPlayers();
    List &GetDroppingObjects();
    Grid &GetGrid();
    Square &GetValidDropSquare();

    void Run();
    void Pause();
    void Resume();
};

#endif