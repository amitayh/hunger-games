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
        MIN_DISTANCE_FROM_PLAYERS   = 2
    };

    enum Status {
        PENDING,
        RUNNING,
        PAUSED,
        ENDED
    };

    unsigned int tick;
    int menuResume, menuQuit;
    Status status;
    Grid grid;
    ObjectsList walls;
    ObjectsList players;
    ObjectsList arrows;
    ObjectsList droppingObjects;
    InfoBox infoBox;
    Menu menu;
    char key;

    void loop();
    void update();
    void updatePlayers();
    void updateArrows();
    void updateDroppingObjects();
    void dropObjects();
    void addObject(Object* object, Grid::Square& square, ObjectsList& list);
    void endGame(Player* winner = NULL);
    void showMenu();
    void draw();
    void draw(ObjectsList& list);

public:
    Game();
    ~Game();

    void run();
    void pause();
    void resume();
    void addBot(int row, int col);
    void addBot(Grid::Square& square);
    void addHuman(int row, int col);
    void addHuman(Grid::Square& square);
    void addWall(int row, int col);
    void addInfoBox(int row, int col);
    void addArrow(Arrow& arrow, Grid::Square& square);
    void clearWall(Grid::Square& square);
    ObjectsList& getPlayers();
    ObjectsList& getDroppingObjects();
    Grid::Square& getValidDropSquare();
    bool isValidDrop(int row, int col);
    bool isValidDrop(const Grid::Square& square);

    const Grid& getGrid() const;
    bool checkProbability(int probability) const;
    unsigned int getTick() const;
    char getKey() const;
};

#endif