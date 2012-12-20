#include "Game.h"
#include "BaseArrow.h"
#include "Bot.h"
#include "Human.h"
#include "Wall.h"
#include "InfoBox.h"
#include "Food.h"
#include "Quiver.h"
#include "Bomb.h"
#include "Console.h"
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <iostream>

using namespace std;

Game::Game() {
    // Initialize random number generator
    srand((unsigned int) time(NULL));

    // Initialize menu
    menuResume = menu.addOption("Resume");
    menuQuit = menu.addOption("Quit");

    // Initialize game
    status = PENDING;
    tick = 0;
}

Game::~Game() {
    // Free memory allocations
    freeObejctsList(players);
    freeObejctsList(arrows);
    freeObejctsList(droppingObjects);
    freeObejctsList(walls);
}

void Game::addPlayer(BasePlayer* player, Grid::Square& square) {
    addObject(player, square, players);
}

void Game::addPlayer(BasePlayer* player, int row, int col) {
    addPlayer(player, grid.getSquare(row, col));
}

void Game::addWall(Grid::Square& square) {
    if (!square.hasWall()) {
        addObject(new Wall, square, walls);
    }
}

void Game::addWall(int row, int col) {
    addWall(grid.getSquare(row, col));
}

void Game::addInfoBox(Grid::Square& square) {
    infoBox.setGame(*this);
    infoBox.setSquare(square);
}

void Game::addInfoBox(int row, int col) {
    addInfoBox(grid.getSquare(row, col));
}

void Game::addArrow(BaseArrow* arrow, Grid::Square& square) {
    // The arrow is pre-allocated by the shooting player
    addObject(arrow, square, arrows);
}

void Game::addArrow(BaseArrow* arrow, int row, int col) {
    addArrow(arrow, grid.getSquare(row, col));
}

void Game::addObject(BaseObject* object, Grid::Square& square, ObjectsList& list) {
    object->setGame(*this);
    object->setSquare(square);
    list.push_back(object);
}

void Game::clearWall(const Wall& wall) {
    ObjectsIterator it = find(walls.begin(), walls.end(), &wall);
    if (it != walls.end()) {
        wall.getSquare().unsetWall();
        delete *it;
        walls.erase(it);
    }
}

bool Game::checkProbability(int probability) const {
    int random = rand() % 100;
    return (random < probability);
}

void Game::run() {
    status = RUNNING;
    Console::clear();
    drawObejctsList(walls);
    loop();
}

void Game::pause() {
    status = PAUSED;
}

void Game::resume() {
    status = RUNNING;
    Console::clear();
    drawObejctsList(walls);
    drawObejctsList(droppingObjects);
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
                drawUpdatingObjects();
                dropObjects();
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
    ObjectsIterator it = arrows.begin();
    while (it != arrows.end()) {
        BaseArrow* arrow = (BaseArrow*) *it;
        arrow->update();
        if (arrow->getHit()) {
            // Arrow hit a wall/player - remove it
            it = arrows.erase(it);
            delete arrow;
        } else {
            it++;
        }
    }
}

void Game::updatePlayers() {
    ObjectsIterator it = players.begin();
    while (status == RUNNING && it != players.end()) {
        BasePlayer* player = (BasePlayer*) *it;
        player->update();
        if (!player->isAlive()) {
            // Player is dead - remove him
            it = players.erase(it);
            delete player;

            if (players.size() == 1) {
                // One player left, game over
                endGame((BasePlayer*) players.front());
            }
        } else {
            it++;
        }
    }
}

void Game::updateDroppingObjects() {
    ObjectsIterator it = droppingObjects.begin();
    while (status == RUNNING && it != droppingObjects.end()) {
        DroppingObject* droppingObject = (DroppingObject*) *it;
        if (droppingObject->getPickedUp()) {
            // Object was picked up by a player - remove it
            it = droppingObjects.erase(it);
            delete droppingObject;
        } else {
            it++;
        }
    }
}

void Game::drawUpdatingObjects() {
    // Draw updating objects
    drawObejctsList(arrows);
    drawObejctsList(players);
    infoBox.draw();
    Console::gotoPosition(grid.getRows(), grid.getCols()); // Hide cursor from main window
}

void Game::drawObejctsList(ObjectsList& list) {
    ObjectsIterator it = list.begin();
    while (it != list.end()) {
        (*it)->draw();
        it++;
    }
}

void Game::freeObejctsList(ObjectsList& list) {
    ObjectsIterator it = list.begin();
    while (it != list.end()) {
        delete *it;
        it = list.erase(it);
    }
}

void Game::dropObjects() {
    if (checkProbability(DROP_FOOD_PROBABILITY)) {
        addObject(new Food, getValidDropSquare(), droppingObjects);
    }
    if (checkProbability(DROP_QUIVER_PROBABILITY)) {
        addObject(new Quiver, getValidDropSquare(), droppingObjects);
    }
    if (checkProbability(DROP_BOMB_PROBABILITY)) {
        addObject(new Bomb, getValidDropSquare(), droppingObjects);
    }
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
        ObjectsIterator it = players.begin();
        while (result && it != players.end()) {
            double distance = square.getDistance((*it)->getSquare());
            if (distance <= MIN_DISTANCE_FROM_PLAYERS) {
                // Found a player closer than the minimum distance allowed
                result = false;
            }
            it++;
        }
    }
    return result;
}

unsigned int Game::getTick() const {
    return tick;
}

ObjectsList& Game::getPlayers() {
    return players;
}

ObjectsList& Game::getDroppingObjects() {
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