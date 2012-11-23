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

void Game::addPlayer(Grid::Square& square) {
    // Name the players sequentially (A, B, C...)
    char name = 'A' + players.getSize();
    players.push(new Player(name, square));
}

void Game::addWall(int row, int col) {
    Grid::Square& square = grid.getSquare(row, col);
    if (!square.hasWall()) {
        walls.push(new Wall(square));
    }
}

void Game::addInfoBox(int row, int col) {
    Dimensions size = infoBox.getSize();
    int width = size.getWidth(), height = size.getHeight();

    // Add walls around the info box
    for (int i = 0; i < width + 2; i++) {
        addWall(row - 1, col + i - 1);
        addWall(row + height, col + i - 1);
    }
    for (int i = 0; i < height; i++) {
        addWall(row + i, col - 1);
        addWall(row + i, col + width);
    }

    infoBox.setSquare(grid.getSquare(row, col));
}

void Game::addArrow(const Arrow& arrow) {
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

void Game::updateArrows() {
    List::Iterator it(arrows);
    while (!it.done()) {
        List::Node* node = it.getCurrent();
        Arrow* arrow = (Arrow*) node->getData();
        arrow->update(*this);
        if (arrow->getHit()) {
            // Arrow hit a wall/player - remove it
            arrows.remove(node);
            delete arrow;
        }
    }
}

void Game::updatePlayers() {
    List::Iterator it(players);
    while (status == RUNNING && !it.done()) {
        List::Node* node = it.getCurrent();
        Player* player = (Player*) node->getData();
        player->update(*this);
        if (!player->getPower()) {
            // Player is dead - remove him
            players.remove(node);
            delete player;

            if (players.getSize() == 1) {
                // One player left, game over
                endGame((Player*) players.peek());
            }
        }
    }
}

void Game::updateDroppingObjects() {
    List::Iterator it(droppingObjects);
    while (status == RUNNING && !it.done()) {
        List::Node* node = it.getCurrent();
        DroppingObject* droppingObject = (DroppingObject*) node->getData();
        if (droppingObject->getPickedUp()) {
            // Object was picked up by a player - remove it
            droppingObjects.remove(node);
            delete droppingObject;
        }
    }
}

void Game::draw() const {
    // Draw updating objects
    drawArrows();
    drawPlayers();
    infoBox.draw(players);
    gotoxy(grid.getCols(), grid.getRows()); // Hide cursor from main window
}

void Game::drawArrows() const {
    List::Iterator it(arrows);
    while (!it.done()) {
        List::Node* node = it.getCurrent();
        Arrow* arrow = (Arrow*) node->getData();
        arrow->draw();
    }
}

void Game::drawPlayers() const {
    List::Iterator it(players);
    while (!it.done()) {
        List::Node* node = it.getCurrent();
        Player* player = (Player*) node->getData();
        player->draw();
    }
}

void Game::drawDroppingObjects() const {
    List::Iterator it(droppingObjects);
    while (!it.done()) {
        List::Node* node = it.getCurrent();
        DroppingObject* droppingObject = (DroppingObject*) node->getData();
        droppingObject->draw();
    }
}

void Game::drawWalls() const {
    List::Iterator it(walls);
    while (!it.done()) {
        List::Node* node = it.getCurrent();
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
    DroppingObject* object = new DroppingObject(type, getValidDropSquare());
    droppingObjects.push(object);
    object->draw();
}

Grid::Square& Game::getValidDropSquare() const {
    Grid::Square* square = &grid.getRandomSquare();
    while (!isValidDrop(*square)) {
        // Try again until the random square is a valid drop zone
        square = &grid.getRandomSquare();
    }
    return *square;
}

bool Game::isValidDrop(const Grid::Square& square) const {
    bool result = true;
    if (!square.isEmpty()) {
        // Square is occupied
        result = false;
    } else if (infoBox.inArea(square)) {
        // Square is in the info box's area
        result = false;
    } else {
        // Check if the square is too close to the players
        List::Iterator it(players);
        while (result && !it.done()) {
            List::Node* node = it.getCurrent();
            Player* player = (Player*) node->getData();
            double distance = square.getDistance(player->getSquare());
            if (distance <= MIN_DISTANCE_FROM_PLAYERS) {
                // Found a player closer than the minimum distance allowed
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