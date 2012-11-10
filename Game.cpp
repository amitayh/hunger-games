#include "Game.h"
#include "Wall.h"
#include "InfoBox.h"
#include "Food.h"
#include "Quiver.h"
#include "Bomb.h"

bool checkProbability(int probability) {
    int random = rand() % 100;
    return (random < probability);
}

Game::Game() {
    tick = 0;
    fps = FRAMES_PER_SECOND;
    grid.Init(DEFAULT_NUM_ROWS, DEFAULT_NUM_COLS);
}

Game::~Game() {
    Object* object;
    ObjectsIterator it = objects.begin();
    while (it != objects.end()) {
        object = *it;
        it = objects.erase(it);
        delete object;
    }
}

void Game::AddPlayer(int row, int col) {
    char name = 'A' + players.size();
    Player* player = new Player(name);
    AddObject(player, row, col);
    players.push_front(player);
}

void Game::AddWall(int row, int col) {
    Square* square = grid.GetSquare(row, col);
    if (!square->GetWall()) {
        AddObject(new Wall, square);
    }
}

void Game::AddInfoBox(int row, int col) {
    Dimensions* size = infoBox.GetSize();

    // Add walls around the info box
    for (int i = 0; i < size->GetWidth() + 2; i++) {
        AddWall(row - 1, col + i - 1);
        AddWall(row + size->GetHeight(), col + i - 1);
    }
    for (int i = 0; i < size->GetHeight(); i++) {
        AddWall(row + i, col - 1);
        AddWall(row + i, col + size->GetWidth());
    }

    AddObject(&infoBox, row, col);
}

void Game::AddObject(Object* object, int row, int col) {
    AddObject(object, grid.GetSquare(row, col));
}

void Game::AddObject(Object* object, Square* square) {
    object->SetGame(this);
    object->SetSquare(square);
    objects.push_front(object);
}

void Game::RemoveObject(Object* object) {
    objects.remove(object);
    delete object;
}

void Game::RemovePlayer(Player* player) {
    players.remove(player);
    if (players.size() == 1) {
        paused = true;
    }
}

void Game::Run() {
    paused = false;
    Loop();
}

void Game::Pause() {
    paused = true;
}

void Game::Loop() {
    while (!paused) {
        Update();
        //CheckCollisions();
        DropObjects();
        Draw();
        tick++;
        Sleep(1000 / fps);
    }
}

void Game::Update() {
    Object* object;
    ObjectsIterator it = objects.begin();
    while (it != objects.end()) {
        object = *it;
        if (object->Update()) {
            // Update OK, continue to next object
            it++;
        } else {
            // Object is ready for removal
            it = objects.erase(it);
            delete object;
        }
    }
}

void Game::CheckCollisions() {
    ObjectsIterator it = objects.begin();
    while (it != objects.end()) {
        it++;
    }
}

void Game::DropObjects() {
    if (checkProbability(DROP_FOOD_PROBABILITY)) {
        DropObject(new Food);
    }
    if (checkProbability(DROP_QUIVER_PROBABILITY)) {
        DropObject(new Quiver);
    }
    if (checkProbability(DROP_BOMB_PROBABILITY)) {
        DropObject(new Bomb);
    }
}

void Game::DropObject(DroppingObject* object) {
    int row = rand() % grid.GetRows(),
        col = rand() % grid.GetCols();
    Square* square = grid.GetSquare(row, col);
    if (IsValidSquare(square)) {
        square->SetDroppingObject(object);
        AddObject(object, square);
    } else {
        // Square is occupied, try again...
        DropObject(object);
    }
}

bool Game::IsValidSquare(Square* square) {
    if (square->IsEmpty()) {
        Square* infoBoxSquare = infoBox.GetSquare();
        Dimensions* infoBoxSize = infoBox.GetSize();
        
        int row = square->GetRow(),
            col = square->GetCol(),
            rowMin = infoBoxSquare->GetRow(),
            rowMax = rowMin + infoBoxSize->GetHeight(),
            colMin = infoBoxSquare->GetCol(),
            colMax = colMin + infoBoxSize->GetWidth();

        return !(row >= rowMin && row <= rowMax && col >= colMin && col <= colMax);

        // TODO: check players 2 squares away
    }
    return false;
}

void Game::Draw() {
    clrscr();
    ObjectsIterator it = objects.begin();
    while (it != objects.end()) {
        (*it)->Draw();
        it++;
    }
}

int Game::GetTick() {
    return tick;
}

Grid* Game::GetGrid() {
    return &grid;
}

PlayersList* Game::GetPlayers() {
    return &players;
}