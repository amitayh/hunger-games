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
        FRAMES_PER_SECOND           = 30,
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

    void loop();
    void update();
    void updatePlayers();
    void updateArrows();
    void updateDroppingObjects();
    void dropObjects();
    void dropObject(DroppingObject::Type type);
    void endGame(const Player* winner = NULL);
    void showMenu();

    void draw() const;
    void drawPlayers() const;
    void drawArrows() const;
    void drawDroppingObjects() const;
    void drawWalls() const;
    bool isValidDrop(const Grid::Square& square) const;

public:
    Game();
    ~Game();

    void run();
    void pause();
    void resume();
    void addPlayer(int row, int col);
    void addPlayer(Grid::Square& square);
    void addWall(int row, int col);
    void addInfoBox(int row, int col);
    void addArrow(const Arrow& arrow);
    
    const List& getPlayers() const;
    const List& getDroppingObjects() const;
    const Grid& getGrid() const;
    Grid::Square& getValidDropSquare() const;
    bool checkProbability(int probability) const;
    unsigned int getTick() const;
};

#endif