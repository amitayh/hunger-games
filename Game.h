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

    enum Status {
        PENDING,
        RUNNING,
        PAUSED,
        ENDED
    };

    unsigned int tick;
    Status status;
    Grid grid;
    List walls;
    List players;
    List arrows;
    List droppingObjects;
    InfoBox infoBox;
    Menu menu;

    void Loop();
    void Update();
    void UpdatePlayers();
    void UpdateArrows();
    void UpdateDroppingObjects();
    void DropObjects();
    void DropObject(DroppingObject::Type type);
    void EndGame(const Player *winner = NULL);
    void ShowMenu();

    void Draw() const;
    void DrawPlayers() const;
    void DrawArrows() const;
    void DrawDroppingObjects() const;
    void DrawWalls() const;
    bool IsValidDrop(const Square &square) const;

public:
    Game();
    ~Game();

    void Run();
    void Pause();
    void Resume();
    void AddPlayer(int row, int col);
    void AddPlayer(Square &square);
    void AddWall(int row, int col);
    void AddInfoBox(int row, int col);
    void AddArrow(Arrow &arrow);
    
    const List &GetPlayers() const;
    const List &GetDroppingObjects() const;
    const Grid &GetGrid() const;
    Square &GetValidDropSquare() const;
    bool CheckProbability(int probability) const;
    unsigned int GetTick() const;
};

#endif