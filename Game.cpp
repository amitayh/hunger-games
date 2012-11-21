#include "Game.h"
#include "Arrow.h"
#include "Player.h"
#include "Wall.h"
#include "InfoBox.h"
#include <time.h>
#include <conio.h>

Game::Game() {
    tick = 0;
    srand((unsigned int) time(NULL));
    menu.AddOption("Resume");
    menu.AddOption("Quit");
}

Game::~Game() {
    // Delete walls
    while (!walls.IsEmpty()) {
        delete walls.Pop();
    }
    // Delete players
    while (!players.IsEmpty()) {
        delete players.Pop();
    }
    // Delete arrows
    while (!arrows.IsEmpty()) {
        delete arrows.Pop();
    }
    // Delete dropping objects
    while (!droppingObjects.IsEmpty()) {
        delete droppingObjects.Pop();
    }
}

void Game::AddPlayer(int row, int col) {
    AddPlayer(grid.GetSquare(row, col));
}

void Game::AddPlayer(Square &square) {
    char name = 'A' + players.GetSize();
    players.Push(new Player(name, square));
}

void Game::AddWall(int row, int col) {
    Square &square = grid.GetSquare(row, col);
    if (!square.HasWall()) {
        walls.Push(new Wall(square));
    }
}

void Game::AddInfoBox(int row, int col) {
    Dimensions size = infoBox.GetSize();

    // Add walls around the info box
    for (int i = 0; i < size.GetWidth() + 2; i++) {
        AddWall(row - 1, col + i - 1);
        AddWall(row + size.GetHeight(), col + i - 1);
    }
    for (int i = 0; i < size.GetHeight(); i++) {
        AddWall(row + i, col - 1);
        AddWall(row + i, col + size.GetWidth());
    }

    infoBox.SetSquare(grid.GetSquare(row, col));
}

void Game::AddArrow(Arrow &arrow) {
    arrows.Push(&arrow);
}

bool Game::CheckProbability(int probability) const {
    int random = rand() % 100;
    return (random < probability);
}

void Game::Run() {
    running = true;
    DrawWalls();
    Loop();
}

void Game::Pause() {
    running = false;
}

void Game::Resume() {
    running = true;
    clrscr();
    DrawWalls();
    DrawDroppingObjects();
    Draw();
}

void Game::EndGame(const Player *winner) {
    Pause();
    clrscr();
    gotoxy(0, 0);
    ChangeColor(SILVER);
    cout << "Game over";
    if (winner) {
        cout << ", winner is " << winner->GetName();
    }
    cout << "!" << endl;
}

void Game::Loop() {
    while (running) {
        if (kbhit() && getch() == ESCAPSE_KEY) {
            ShowMenu();
        } else if (Update()) {
            Draw();
            DropObjects();
            tick++;
            Sleep(1000 / FRAMES_PER_SECOND);
        }
    }
}

void Game::ShowMenu() {
    Pause();
    switch (menu.Choose()) {
        case MENU_RESUME:
            Resume();
            break;
        case MENU_QUIT:
            EndGame();
            break;
    }
}

bool Game::Update() {
    UpdateArrows();
    UpdatePlayers();
    UpdateDroppingObjects();
    return running;
}

void Game::Draw() {
    DrawArrows();
    DrawPlayers();
    infoBox.Draw(players);
    gotoxy(grid.GetCols(), grid.GetRows()); // Hide cursor from main window
}

void Game::UpdateArrows() {
    ListIterator it(arrows);
    while (!it.Done()) {
        ListNode *node = it.Current();
        Arrow *arrow = (Arrow *) node->GetData();
        arrow->Update(*this);
        if (arrow->GetHit()) {
            // Arrow hit a wall/player
            arrows.Remove(node);
            delete arrow;
        }
    }
}

void Game::DrawArrows() {
    ListIterator it(arrows);
    while (!it.Done()) {
        ListNode *node = it.Current();
        Arrow *arrow = (Arrow *) node->GetData();
        arrow->Draw();
    }
}

void Game::UpdatePlayers() {
    ListIterator it(players);
    while (running && !it.Done()) {
        ListNode *node = it.Current();
        Player *player = (Player *) node->GetData();
        player->Update(*this);
        if (!player->GetPower()) {
            // Player is dead
            players.Remove(node);
            delete player;

            if (players.GetSize() == 1) {
                // One player left, game over
                EndGame((Player *) players.Peek());
            }
        }
    }
}

void Game::DrawPlayers() {
    ListIterator it(players);
    while (!it.Done()) {
        ListNode *node = it.Current();
        Player *player = (Player *) node->GetData();
        player->Draw();
    }
}

void Game::UpdateDroppingObjects() {
    ListIterator it(droppingObjects);
    while (running && !it.Done()) {
        ListNode *node = it.Current();
        DroppingObject *droppingObject = (DroppingObject *) node->GetData();
        if (droppingObject->GetPickedUp()) {
            droppingObjects.Remove(node);
            delete droppingObject;
        }
    }
}

void Game::DrawDroppingObjects() {
    ListIterator it(droppingObjects);
    while (!it.Done()) {
        ListNode *node = it.Current();
        DroppingObject *droppingObject = (DroppingObject *) node->GetData();
        droppingObject->Draw();
    }
}

void Game::DrawWalls() {
    ListIterator it(walls);
    while (!it.Done()) {
        ListNode *node = it.Current();
        Wall *wall = (Wall *) node->GetData();
        wall->Draw();
    }
}

void Game::DropObjects() {
    if (CheckProbability(DROP_FOOD_PROBABILITY)) {
        DropObject(DroppingObject::Type::FOOD);
    }
    if (CheckProbability(DROP_QUIVER_PROBABILITY)) {
        DropObject(DroppingObject::Type::QUIVER);
    }
    if (CheckProbability(DROP_BOMB_PROBABILITY)) {
        DropObject(DroppingObject::Type::BOMB);
    }
}

void Game::DropObject(DroppingObject::Type type) {
    Square &square = GetValidDropSquare();
    DroppingObject *object = new DroppingObject(type, square);
    droppingObjects.Push(object);
    object->Draw();
}

Square &Game::GetValidDropSquare() {
    Square *square = &grid.GetRandomSquare();
    do {
        square = &grid.GetRandomSquare();
    } while (!IsValidDrop(*square));
    return *square;
}

bool Game::IsValidDrop(Square &square) {
    bool result = true;
    if (!square.IsEmpty()) {
        // Square is occupied
        result = false;
    } else if (infoBox.InArea(square)) {
        // Square is in the info box's area
        result = false;
    } else {
        ListIterator it(players);
        while (result && !it.Done()) {
            ListNode *node = it.Current();
            Player *player = (Player *) node->GetData();
            double distance = square.GetDistance(player->GetSquare());
            if (distance <= MIN_DISTANCE_FROM_PLAYERS) {
                // Square is too close to one of the players
                result = false;
            }
        }
    }
    return result;
}

unsigned int Game::GetTick() const {
    return tick;
}

List &Game::GetPlayers() {
    return players;
}

List &Game::GetDroppingObjects() {
    return droppingObjects;
}

Grid &Game::GetGrid() {
    return grid;
}