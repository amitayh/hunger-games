#ifndef _GAME_H
#define _GAME_H

#include "Grid.h"
#include "InfoBox.h"
#include "Menu.h"

namespace HungerGames
{

    class Bot;
    class BaseArrow;
    class EventsFile;
    class ObjectsDropper;

    class Game
    {
        static const int ESCAPSE_KEY;
        static const int FRAMES_PER_SECOND;
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
        ObjectsDropper* pObjectsDropper;
        char key;

        void loop();
        void update();
        void updatePlayers();
        void updateArrows();
        void updateDroppingObjects();
        void addObject(BaseObject* object, Grid::Square& square, ObjectsList& list);
        void endGame(BasePlayer* winner = NULL);
        void showMenu();
        void drawUpdatingObjects();
        void drawObejctsList(ObjectsList& list);
        void freeObejctsList(ObjectsList& list);

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
        void addPlayer(BasePlayer* player, Grid::Square& square);
        void addPlayer(BasePlayer* player, int row, int col);
        void addArrow(BaseArrow* arrow, Grid::Square& square);
        void addArrow(BaseArrow* arrow, int row, int col);
        void dropObject(DroppingObject* object);
        void clearWall(const Wall& wall);
        ObjectsList& getPlayers();
        ObjectsList& getDroppingObjects();
        Grid::Square& getValidDropSquare();
        bool isValidDrop(int row, int col);
        bool isValidDrop(const Grid::Square& square);
        void setObjectsDropper(ObjectsDropper* dropper);

        const Grid& getGrid() const;
        bool isRunning() const;
        unsigned int getTick() const;
        char getKey() const;
    };

}

#endif