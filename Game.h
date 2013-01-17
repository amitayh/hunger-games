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

    typedef list<Wall*> WallsList;
    typedef list<BaseArrow*> ArrowsList;
    typedef list<DroppingObject*> DroppingObjectsList;

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
        WallsList walls;
        PlayersList players;
        ArrowsList arrows;
        DroppingObjectsList droppingObjects;
        InfoBox infoBox;
        Menu menu;
        ObjectsDropper* pObjectsDropper;
        char key;

        void loop();
        void update();
        void updatePlayers();
        void updateArrows();
        void updateDroppingObjects();
        void endGame(BasePlayer* winner = NULL);
        void showMenu();
        void drawUpdatingObjects();
        template<class T> void addObject(T& object, Grid::Square& square, list<T*>& list);

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
        void addPlayer(BasePlayer& player, Grid::Square& square);
        void addPlayer(BasePlayer& player, int row, int col);
        void addArrow(BaseArrow& arrow, Grid::Square& square);
        void addArrow(BaseArrow& arrow, int row, int col);
        void dropObject(DroppingObject& object);
        void clearWall(const Wall& wall);
        PlayersList& getPlayers();
        DroppingObjectsList& getDroppingObjects();
        Grid::Square& getValidDropSquare();
        bool isValidDrop(int row, int col);
        bool isValidDrop(const Grid::Square& square);
        void setObjectsDropper(ObjectsDropper& dropper);

        const Grid& getGrid() const;
        bool isRunning() const;
        unsigned int getTick() const;
        char getKey() const;
    };

    // Template methods should be implemented in header file

    template<class T>
    void Game::addObject(T& object, Grid::Square& square, list<T*>& list) {
        object.setGame(*this);
        object.setSquare(square);
        list.push_back(&object);
    }

}

#endif