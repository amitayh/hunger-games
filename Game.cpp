#include "Game.h"
#include "BaseArrow.h"
#include "BasePlayer.h"
#include "Wall.h"
#include "InfoBox.h"
#include "Food.h"
#include "Quiver.h"
#include "Bomb.h"
#include "Console.h"
#include "ObjectsDropper.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace HungerGames;

const int Game::ESCAPSE_KEY                = 27;
const int Game::FRAMES_PER_SECOND          = 25;
const int Game::MIN_DISTANCE_FROM_PLAYERS  = 2;

Game::Game() {
    // Initialize menu
    menuResume = menu.addOption("Resume");
    menuQuit = menu.addOption("Quit");

    // Initialize info box
    infoBox.setGame(*this);

    // Initialize game
    pObjectsDropper = NULL;
    status = PENDING;
    tick = 1;
}

Game::~Game() {
    // Free memory allocations
    BaseObject::Delete del;
    for_each(players.begin(), players.end(), del);
    for_each(arrows.begin(), arrows.end(), del);
    for_each(droppingObjects.begin(), droppingObjects.end(), del);
    for_each(walls.begin(), walls.end(), del);
    delete pObjectsDropper;
}

void Game::addPlayer(BasePlayer& player, Grid::Square& square) {
    addObject(player, square, players);
}

void Game::addPlayer(BasePlayer& player, int row, int col) {
    addPlayer(player, grid.getSquare(row, col));
}

void Game::addWall(Grid::Square& square) {
    if (!square.hasWall()) {
        Wall* wall = new Wall;
        addObject(*wall, square, walls);
    }
}

void Game::addWall(int row, int col) {
    addWall(grid.getSquare(row, col));
}

void Game::addInfoBox(Grid::Square& square) {
    infoBox.setSquare(square);
}

void Game::addInfoBox(int row, int col) {
    addInfoBox(grid.getSquare(row, col));
}

void Game::addArrow(BaseArrow& arrow, Grid::Square& square) {
    // The arrow is pre-allocated by the shooting player
    addObject(arrow, square, arrows);
}

void Game::addArrow(BaseArrow& arrow, int row, int col) {
    addArrow(arrow, grid.getSquare(row, col));
}

void Game::dropObject(DroppingObject& object) {
    // The object is pre-allocated by the objects dropper
    addObject(object, getValidDropSquare(), droppingObjects);
}

void Game::clearWall(const Wall& wall) {
    WallsList::iterator it = find(walls.begin(), walls.end(), &wall);
    if (it != walls.end()) {
        wall.getSquare().unsetWall();
        delete *it;
        walls.erase(it);
    }
}

void Game::run() {
    status = RUNNING;
    Console::clear();
    for_each(walls.begin(), walls.end(), BaseObject::Draw());
    loop();
}

void Game::pause() {
    status = PAUSED;
}

void Game::resume() {
    status = RUNNING;
    Console::clear();
    BaseObject::Draw draw;
    for_each(walls.begin(), walls.end(), draw);
    for_each(droppingObjects.begin(), droppingObjects.end(), draw);
    drawUpdatingObjects();
}

void Game::endGame(BasePlayer* winner) {
    status = ENDED;
    Console::clear();
    Console::gotoPosition(0, 0);
    Console::changeColor(Console::SILVER);
    cout << "Game over";
    if (winner) {
        // Print winner's name
        cout << ", winner is " << winner->getName();
    }
    cout << "!" << endl;
}

void Game::loop() {
    // Main game loop
    while (status == RUNNING) {
        key = kbhit() ? getch() : '\0';
        if (key == ESCAPSE_KEY) {
            // User pressed escape - show menu
            showMenu();
        } else {
            update();
            if (status == RUNNING) { // Status may change after the update
                drawUpdatingObjects(); // Draw
                if (pObjectsDropper) { // Drop
                    pObjectsDropper->drop(*this);
                }
                tick++;
                Sleep(1000 / FRAMES_PER_SECOND);
            }
        }
    }
}

void Game::showMenu() {
    pause();
    int option = menu.choose();
    if (option == menuResume) {
        resume();
    } else if (option == menuQuit) {
        endGame();
    }
}

void Game::update() {
    updateArrows();
    updatePlayers();
    updateDroppingObjects();
}

void Game::updateArrows() {
    ArrowsList::iterator it = arrows.begin();
    while (it != arrows.end()) {
        BaseArrow* arrow = *it;
        arrow->update();
        if (arrow->getHit()) {
            // Arrow hit a wall/player - remove it
            it = arrows.erase(it);
            delete arrow;
        } else {
            ++it;
        }
    }
}

void Game::updatePlayers() {
    PlayersList::iterator it = players.begin();
    while (status == RUNNING && it != players.end()) {
        BasePlayer* player = *it;
        player->update();
        if (!player->isAlive()) {
            // Player is dead - remove him
            it = players.erase(it);
            delete player;

            if (players.size() == 1) {
                // One player left, game over
                endGame(players.front());
            }
        } else {
            ++it;
        }
    }
}

void Game::updateDroppingObjects() {
    DroppingObjectsList::iterator it = droppingObjects.begin();
    while (status == RUNNING && it != droppingObjects.end()) {
        DroppingObject* droppingObject = *it;
        if (droppingObject->getPickedUp()) {
            // Object was picked up by a player - remove it
            it = droppingObjects.erase(it);
            delete droppingObject;
        } else {
            ++it;
        }
    }
}

void Game::drawUpdatingObjects() {
    // Draw updating objects
    BaseObject::Draw draw;
    for_each(arrows.begin(), arrows.end(), draw);
    for_each(players.begin(), players.end(), draw);
    infoBox.draw();
    Console::gotoPosition(grid.getRows(), grid.getCols()); // Hide cursor from main window
}

Grid::Square& Game::getValidDropSquare() {
    Grid::Square* square = &grid.getRandomSquare();
    while (!isValidDrop(*square)) {
        // Try again until the random square is a valid drop zone
        square = &grid.getRandomSquare();
    }
    return *square;
}

bool Game::isValidDrop(int row, int col) {
    return isValidDrop(grid.getSquare(row, col));
}

bool Game::isValidDrop(const Grid::Square& square) {
    bool result = true;
    if (!square.isEmpty()) {
        // Square is occupied
        result = false;
    } else if (infoBox.inArea(square)) {
        // Square is in the info box's area
        result = false;
    } else {
        // Check if the square is too close to the players
        PlayersList::iterator it = players.begin();
        while (result && it != players.end()) {
            double distance = square.getDistance((*it)->getSquare());
            if (distance <= MIN_DISTANCE_FROM_PLAYERS) {
                // Found a player closer than the minimum distance allowed
                result = false;
            }
            ++it;
        }
    }
    return result;
}

void Game::setObjectsDropper(ObjectsDropper& dropper) {
    pObjectsDropper = &dropper;
}

unsigned int Game::getTick() const {
    return tick;
}

PlayersList& Game::getPlayers() {
    return players;
}

DroppingObjectsList& Game::getDroppingObjects() {
    return droppingObjects;
}

const Grid& Game::getGrid() const {
    return grid;
}

char Game::getKey() const {
    return key;
}

bool Game::isRunning() const {
    return (status == RUNNING);
}