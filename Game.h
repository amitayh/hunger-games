#ifndef _GAME_H
#define _GAME_H

#include "Grid.h"
#include "Bot.h"
#include "Arrow.h"
#include "InfoBox.h"
#include "Menu.h"
#include "DroppingObject.h"
#include <iostream>

using namespace std;

class Game
{
    static const int ESCAPSE_KEY;
    static const int FRAMES_PER_SECOND;
    static const int DROP_FOOD_PROBABILITY;
    static const int DROP_QUIVER_PROBABILITY;
    static const int DROP_BOMB_PROBABILITY;
    static const int MIN_DISTANCE_FROM_PLAYERS;

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
    void addObject(BaseObject* object, Grid::Square& square, ObjectsList& list);
    void endGame(BasePlayer* winner = NULL);
    void showMenu();
    void drawUpdatingObjects();
    void drawObejctsList(ObjectsList& list);

public:
    Game();
    ~Game();

    void run();
    void pause();
    void resume();
    void addWall(Grid::Square& square);
    void addWall(int row, int col);
    void addInfoBox(Grid::Square& square);
    void addInfoBox(int row, int col);
    void addHuman(Grid::Square& square);
    void addHuman(int row, int col);
    void addBot(Bot* bot, Grid::Square& square);
    void addBot(Bot* bot, int row, int col);
    void addArrow(Arrow* arrow, Grid::Square& square);
    void addArrow(Arrow* arrow, int row, int col);
    void clearWall(const Wall& wall);
    ObjectsList& getPlayers();
    ObjectsList& getDroppingObjects();
    Grid::Square& getValidDropSquare();
    bool isValidDrop(int row, int col);
    bool isValidDrop(const Grid::Square& square);

    const Grid& getGrid() const;
    bool checkProbability(int probability) const;
    bool isRunning() const;
    unsigned int getTick() const;
    char getKey() const;
};

#endif