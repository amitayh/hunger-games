#include "Game.h"
#include "Wall.h"
#include "InfoBox.h"
#include "Food.h"
#include "Quiver.h"
#include "Bomb.h"
#include <time.h>
#include <conio.h>

Game::Game():
    tick(0),
    fps(FRAMES_PER_SECOND),
    grid(DEFAULT_NUM_ROWS, DEFAULT_NUM_COLS)
{
    srand((unsigned int) time(NULL));
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
    if (!square->GetWall()) {
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

void Game::AddArrow(Arrow* arrow, Square* square) {
    AddObject(arrow, square);
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
    clrscr();
    DrawWalls();
    DrawDroppingObjects();
    Draw();
}

void Game::EndGame(Player* winner) {
    clrscr();
    gotoxy(0, 0);
    cout << "Game over";
    if (winner) {
        cout << ", winner is " << winner->GetName();
    }
    getchar();
}

void Game::Loop() {
    while (!paused) {
        if (kbhit() && getch() == ESCAPSE_KEY) {
            ShowMenu();
        } else {
            Update();
            Draw();
            DropObjects();
            tick++;
            Sleep(1000 / fps);
        }
    }
}

void Game::ShowMenu() {
    Pause();
    switch (menu.Choose()) {
        case RESUME:
            Resume();
            break;
        case QUIT:
            EndGame();
            break;
    }
}

void Game::Update() {
    UpdateArrows();
    UpdatePlayers();
    UpdateDroppingObjects();
}

void Game::Draw() {
    DrawArrows();
    DrawPlayers();
    infoBox.Draw();
    gotoxy(grid.GetCols(), grid.GetRows()); // Hide cursor from main window
}

void Game::UpdateArrows() {
    Arrow* arrow;
    ArrowsIterator it = arrows.begin();
    while (it != arrows.end()) {
        arrow = *it;
        if (!arrow->GetHit()) {
            arrow->Update();
            it++;
        } else {
            // Arrow hit a wall/player
            it = arrows.erase(it);
            delete arrow;
        }
    }
}

void Game::DrawArrows() {
    ArrowsIterator it = arrows.begin();
    while (it != arrows.end()) {
        (*it)->Draw();
        it++;
    }
}

void Game::UpdatePlayers() {
    Player* player;
    PlayersIterator it = players.begin();
    while (it != players.end()) {
        player = *it;
        if (player->GetPower() > 0) {
            // Player is still alive
            player->Update();
            it++;
        } else {
            // Player is dead
            it = players.erase(it);
            delete player;

            if (players.size() == 1) {
                // Game over
                Pause();
                EndGame(players.front());
            }
        }
    }

    /*
    Square* square;
    it = players.begin();
    while (it != players.end()) {
        square = (*it)->GetSquare();
        square->Battle();
    }
    */
}

void Game::DrawPlayers() {
    PlayersIterator it = players.begin();
    while (it != players.end()) {
        (*it)->Draw();
        it++;
    }
}

void Game::UpdateDroppingObjects() {
    DroppingObject* droppingObject;
    DroppingObjectsIterator it = droppingObjects.begin();
    while (it != droppingObjects.end()) {
        droppingObject = *it;
        if (droppingObject->GetPickedUp()) {
            // Object was picked up
            it = droppingObjects.erase(it);
            delete droppingObject;
        } else {
            it++;
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
    if (CheckProbability(DROP_FOOD_PROBABILITY)) {
        DropObject(new Food);
    }
    if (CheckProbability(DROP_QUIVER_PROBABILITY)) {
        DropObject(new Quiver);
    }
    if (CheckProbability(DROP_BOMB_PROBABILITY)) {
        DropObject(new Bomb);
    }
}

void Game::DropObject(DroppingObject* object) {
    int row = rand() % grid.GetRows(),
        col = rand() % grid.GetCols();
    Square* square = grid.GetSquare(row, col);
    if (IsValidDrop(square)) {
        AddObject(object, square);
        droppingObjects.push_back(object);
        object->Draw();
    } else {
        // Try again...
        DropObject(object);
    }
}

bool Game::IsValidDrop(Square* square) {
    bool result = true;
    if (!square->IsEmpty()) {
        // Square is occupied
        result = false;
    } else if (infoBox.InArea(square)) {
        // Square is in the info box's area
        result = false;
    } else {
        PlayersIterator it = players.begin();
        while (result && it != players.end()) {
            double distance = square->GetDistance((*it)->GetSquare());
            if (distance < 2) {
                // Square is too close to one of the players
                result = false;
            }
            it++;
        }
    }
    return result;
}

unsigned int Game::GetTick() {
    return tick;
}

Grid* Game::GetGrid() {
    return &grid;
}

PlayersList* Game::GetPlayers() {
    return &players;
}