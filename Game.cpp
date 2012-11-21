#include "Game.h"
#include "Arrow.h"
#include "Player.h"
#include "Wall.h"
#include "InfoBox.h"
#include <time.h>
#include <conio.h>

Game::Game() {
    // Initialize random number generator
    srand((unsigned int) time(NULL));

    // Initialize menu
    menu.addOption("Resume");
    menu.addOption("Quit");

    // Initialize game
    status = PENDING;
    tick = 0;
}

Game::~Game() {
    // Delete walls
    while (!walls.isEmpty()) {
        delete walls.pop();
    }
    // Delete players
    while (!players.isEmpty()) {
        delete players.pop();
    }
    // Delete arrows
    while (!arrows.isEmpty()) {
        delete arrows.pop();
    }
    // Delete dropping objects
    while (!droppingObjects.isEmpty()) {
        delete droppingObjects.pop();
    }
}

void Game::addPlayer(int row, int col) {
    addPlayer(grid.getSquare(row, col));
}

void Game::addPlayer(Square& square) {
    // Name the players sequentially (A, B, C...)
    char name = 'A' + players.getSize();
    players.push(new Player(name, square));
}

void Game::addWall(int row, int col) {
    Square& square = grid.getSquare(row, col);
    if (!square.hasWall()) {
        walls.push(new Wall(square));
    }
}

void Game::addInfoBox(int row, int col) {
    Dimensions size = infoBox.getSize();

    // Add walls around the info box
    for (int i = 0; i < size.getWidth() + 2; i++) {
        addWall(row - 1, col + i - 1);
        addWall(row + size.getHeight(), col + i - 1);
    }
    for (int i = 0; i < size.getHeight(); i++) {
        addWall(row + i, col - 1);
        addWall(row + i, col + size.getWidth());
    }

    infoBox.setSquare(grid.getSquare(row, col));
}

void Game::addArrow(Arrow& arrow) {
    // The arrow is pre-allocated by the shooting player
    arrows.push(&arrow);
}

bool Game::checkProbability(int probability) const {
    int random = rand() % 100;
    return (random < probability);
}

void Game::run() {
    status = RUNNING;
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

void Game::endGame(const Player* winner) {
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
        if (kbhit() && getch() == ESCAPSE_KEY) {
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
    switch (menu.choose()) {
        case MENU_RESUME:
            resume();
            break;
        case MENU_QUIT:
            endGame();
            break;
    }
}

void Game::update() {
    updateArrows();
    updatePlayers();
    updateDroppingObjects();
}

void Game::draw() const {
    drawArrows();
    drawPlayers();
    infoBox.draw(players);
    gotoxy(grid.getCols(), grid.getRows()); // Hide cursor from main window
}

void Game::updateArrows() {
    ListIterator it(arrows);
    while (!it.done()) {
        ListNode* node = it.getCurrent();
        Arrow* arrow = (Arrow*) node->getData();
        arrow->update(*this);
        if (arrow->getHit()) {
            // Arrow hit a wall/player
            arrows.remove(node);
            delete arrow;
        }
    }
}

void Game::drawArrows() const {
    ListIterator it(arrows);
    while (!it.done()) {
        ListNode* node = it.getCurrent();
        Arrow* arrow = (Arrow*) node->getData();
        arrow->draw();
    }
}

void Game::updatePlayers() {
    ListIterator it(players);
    while (status == RUNNING && !it.done()) {
        ListNode* node = it.getCurrent();
        Player* player = (Player*) node->getData();
        player->update(*this);
        if (!player->getPower()) {
            // Player is dead
            players.remove(node);
            delete player;

            if (players.getSize() == 1) {
                // One player left, game over
                endGame((Player*) players.peek());
            }
        }
    }
}

void Game::drawPlayers() const {
    ListIterator it(players);
    while (!it.done()) {
        ListNode* node = it.getCurrent();
        Player* player = (Player*) node->getData();
        player->draw();
    }
}

void Game::updateDroppingObjects() {
    ListIterator it(droppingObjects);
    while (status == RUNNING && !it.done()) {
        ListNode* node = it.getCurrent();
        DroppingObject* droppingObject = (DroppingObject*) node->getData();
        if (droppingObject->getPickedUp()) {
            droppingObjects.remove(node);
            delete droppingObject;
        }
    }
}

void Game::drawDroppingObjects() const {
    ListIterator it(droppingObjects);
    while (!it.done()) {
        ListNode* node = it.getCurrent();
        DroppingObject* droppingObject = (DroppingObject*) node->getData();
        droppingObject->draw();
    }
}

void Game::drawWalls() const {
    ListIterator it(walls);
    while (!it.done()) {
        ListNode* node = it.getCurrent();
        Wall* wall = (Wall*) node->getData();
        wall->draw();
    }
}

void Game::dropObjects() {
    if (checkProbability(DROP_FOOD_PROBABILITY)) {
        dropObject(DroppingObject::Type::FOOD);
    }
    if (checkProbability(DROP_QUIVER_PROBABILITY)) {
        dropObject(DroppingObject::Type::QUIVER);
    }
    if (checkProbability(DROP_BOMB_PROBABILITY)) {
        dropObject(DroppingObject::Type::BOMB);
    }
}

void Game::dropObject(DroppingObject::Type type) {
    Square& square = getValidDropSquare();
    DroppingObject* object = new DroppingObject(type, square);
    droppingObjects.push(object);
    object->draw();
}

Square& Game::getValidDropSquare() const {
    Square* square = &grid.getRandomSquare();
    while (!isValidDrop(*square)) {
        // Try again until the random square is a valid drop zone
        square = &grid.getRandomSquare();
    }
    return* square;
}

bool Game::isValidDrop(const Square& square) const {
    bool result = true;
    if (!square.isEmpty()) {
        // Square is occupied
        result = false;
    } else if (infoBox.inArea(square)) {
        // Square is in the info box's area
        result = false;
    } else {
        ListIterator it(players);
        while (result && !it.done()) {
            ListNode* node = it.getCurrent();
            Player* player = (Player*) node->getData();
            double distance = square.getDistance(player->getSquare());
            if (distance <= MIN_DISTANCE_FROM_PLAYERS) {
                // Square is too close to one of the players
                result = false;
            }
        }
    }
    return result;
}

unsigned int Game::getTick() const {
    return tick;
}

const List& Game::getPlayers() const {
    return players;
}

const List& Game::getDroppingObjects() const {
    return droppingObjects;
}

const Grid& Game::getGrid() const {
    return grid;
}