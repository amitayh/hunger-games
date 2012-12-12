#include "Game.h"
#include "Arrow.h"
#include "Bot.h"
#include "Human.h"
#include "Wall.h"
#include "InfoBox.h"
#include "Food.h"
#include "Quiver.h"
#include "Bomb.h"
#include <time.h>
#include <conio.h>

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
    // Delete walls
    ObjectsIterator wall = walls.begin();
    while (wall != walls.end()) {
        delete *wall;
        wall = walls.erase(wall);
    }
    // Delete players
    ObjectsIterator player = players.begin();
    while (player != players.end()) {
        delete *player;
        player = players.erase(player);
    }
    // Delete arrows
    ObjectsIterator arrow = arrows.begin();
    while (arrow != arrows.end()) {
        delete *arrow;
        arrow = arrows.erase(arrow);
    }
    // Delete dropping objects
    ObjectsIterator droppingObject = droppingObjects.begin();
    while (droppingObject != droppingObjects.end()) {
        delete *droppingObject;
        droppingObject = droppingObjects.erase(droppingObject);
    }
}

void Game::addBot(int row, int col) {
    addBot(grid.getSquare(row, col));
}

void Game::addBot(Grid::Square& square) {
    // Name the players sequentially (A, B, C...)
    char name = 'A' + players.size();
    addObject(new Bot(name), square, players);
}

void Game::addHuman(int row, int col) {
    addHuman(grid.getSquare(row, col));
}

void Game::addHuman(Grid::Square& square) {
    addObject(new Human, square, players);
}

void Game::addWall(int row, int col) {
    Grid::Square& square = grid.getSquare(row, col);
    if (!square.hasWall()) {
        addObject(new Wall, square, walls);
    }
}

void Game::addInfoBox(int row, int col) {
    infoBox.setGame(*this);
    infoBox.setSquare(grid.getSquare(row, col));
}

void Game::addArrow(Arrow& arrow, Grid::Square& square) {
    // The arrow is pre-allocated by the shooting player
    addObject(&arrow, square, arrows);
}

void Game::addObject(Object* object, Grid::Square& square, ObjectsList& list) {
    object->setGame(*this);
    object->setSquare(square);
    list.push_back(object);
}

void Game::clearWall(Grid::Square& square) {
    Wall* wall = &square.getWall();
    ObjectsIterator it = find(walls.begin(), walls.end(), wall);
    if (it != walls.end()) {
        square.unsetWall();
        square.clear();
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
    clrscr();
    drawWalls();
    loop();
}

void Game::pause() {
    status = PAUSED;
}

void Game::resume() {
    status = RUNNING;
    clrscr();
    drawWalls();
    drawDroppingObjects();
    draw();
}

void Game::endGame(Player* winner) {
    status = ENDED;
    clrscr();
    gotoxy(0, 0);
    changeColor(SILVER);
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
                draw();
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
        Arrow* arrow = (Arrow*) *it;
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
        Player* player = (Player*) *it;
        player->update();
        if (!player->getPower()) {
            // Player is dead - remove him
            it = players.erase(it);
            delete player;

            if (players.size() == 1) {
                // One player left, game over
                endGame((Player*) players.front());
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

void Game::draw() {
    // Draw updating objects
    drawArrows();
    drawPlayers();
    infoBox.draw();
    gotoxy(grid.getCols(), grid.getRows()); // Hide cursor from main window
}

void Game::drawArrows() {
    ObjectsIterator it = arrows.begin();
    while (it != arrows.end()) {
        (*it)->draw();
        it++;
    }
}

void Game::drawPlayers() {
    ObjectsIterator it = players.begin();
    while (it != players.end()) {
        (*it)->draw();
        it++;
    }
}

void Game::drawDroppingObjects() {
    ObjectsIterator it = droppingObjects.begin();
    while (it != droppingObjects.end()) {
        (*it)->draw();
        it++;
    }
}

void Game::drawWalls() {
    ObjectsIterator it = walls.begin();
    while (it != walls.end()) {
        (*it)->draw();
        it++;
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