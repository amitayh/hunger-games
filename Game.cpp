#include "Game.h"
#include "Wall.h"
#include "InfoBox.h"
#include "Food.h"
#include "Quiver.h"
#include "Bomb.h"
#include <time.h>

Game::Game():
    tick(0),
    fps(FRAMES_PER_SECOND),
    grid(DEFAULT_NUM_ROWS, DEFAULT_NUM_COLS)
{
    srand((unsigned) time(NULL));
}

Game::~Game() {
    // Delete walls
    while (!walls.empty()) {
        delete walls.front();
        walls.pop_front();
    }
    // Delete players
    while (!players.empty()) {
        delete players.front();
        players.pop_front();
    }
    // Delete arrows
    while (!arrows.empty()) {
        delete arrows.front();
        arrows.pop_front();
    }
    // Delete dropping objects
    while (!droppingObjects.empty()) {
        delete droppingObjects.front();
        droppingObjects.pop_front();
    }
}

void Game::AddPlayer(int row, int col) {
    char name = 'A' + players.size();
    Player* player = new Player(name);
    AddObject(player, row, col);
    players.push_back(player);
}

void Game::AddWall(int row, int col) {
    Square* square = grid.GetSquare(row, col);
    if (IsValidSquare(square)) {
        Wall* wall = new Wall;
        AddObject(wall, square);
        walls.push_back(wall);
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

void Game::AddArrow(Arrow* arrow) {
    arrows.push_back(arrow);
}

void Game::AddObject(Object* object, int row, int col) {
    AddObject(object, grid.GetSquare(row, col));
}

void Game::AddObject(Object* object, Square* square) {
    object->SetGame(this);
    object->SetSquare(square);
}

bool Game::CheckProbability(int probability) {
    int random = rand() % 100;
    return (random < probability);
}

void Game::Run() {
    paused = false;
    DrawWalls();
    Loop();
}

void Game::Pause() {
    paused = true;
}

void Game::Resume() {
    paused = false;
}

void Game::Loop() {
    while (!paused) {
        Update();
        //CheckCollisions();
        DropObjects();
        tick++;
        Sleep(1000 / fps);
    }
}

void Game::Update() {
    UpdateArrows();
    UpdatePlayers();
    DrawDroppingObjects();
    infoBox.Draw();
    gotoxy(grid.GetCols(), grid.GetRows());
}

void Game::UpdatePlayers() {
    Player* player;
    PlayersIterator it = players.begin();
    while (it != players.end()) {
        player = *it;
        player->Update();
        if (player->GetPower() > 0) {
            // Player is still alive
            it++;
        } else {
            // Player is dead
            it = players.erase(it);
            delete player;
        }
    }
}

void Game::UpdateArrows() {
    Arrow* arrow;
    ArrowsIterator it = arrows.begin();
    while (it != arrows.end()) {
        arrow = *it;
        arrow->Update();
        if (!arrow->GetHit()) {
            it++;
        } else {
            // Arrow hit a wall/player
            it = arrows.erase(it);
            delete arrow;
        }
    }
}

void Game::DrawDroppingObjects() {
    DroppingObjectsIterator it = droppingObjects.begin();
    while (it != droppingObjects.end()) {
        (*it)->Draw();
        it++;
    }
}

void Game::DrawWalls() {
    WallsIterator it = walls.begin();
    while (it != walls.end()) {
        (*it)->Draw();
        it++;
    }
}

void Game::DropObjects() {
    /*
    if (CheckProbability(DROP_FOOD_PROBABILITY)) {
        DropObject(new Food);
    }
    if (CheckProbability(DROP_QUIVER_PROBABILITY)) {
        DropObject(new Quiver);
    }
    if (CheckProbability(DROP_BOMB_PROBABILITY)) {
        DropObject(new Bomb);
    }
    */
}

/*
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

void Game::Draw() {
    clrscr();
    ObjectsIterator it = objects.begin();
    while (it != objects.end()) {
        (*it)->Draw();
        it++;
    }
}
*/

bool Game::IsValidSquare(Square* square) {
    return square->IsEmpty();

    /*
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
    */
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