#include "Game.h"
#include "gotoxy.h"
#include <windows.h>

using namespace std;

Game::Game() {
    tick = 0;
	fps = FRAMES_PER_SECOND;
	grid.Init(DEFAULT_NUM_ROWS, DEFAULT_NUM_COLS);
}

Game::~Game() {
    ArrowsList::iterator arrowIterator;
    for (arrowIterator = arrows.begin(); arrowIterator != arrows.end(); arrowIterator++) {
        delete *arrowIterator;
    }
}

void Game::Run() {
    paused = false;
    Loop();
}

void Game::Pause() {
    paused = true;
}

void Game::Add(Player* player, int row, int col) {
    Square* square = grid.GetSquare(row, col);
    player->SetGame(this);
    player->SetSquare(square);
    players.push_back(player);
}

void Game::Add(Wall* wall, int row, int col) {
    Square* square = grid.GetSquare(row, col);
    wall->SetGame(this);
    wall->SetSquare(square);
    walls.push_back(wall);
}

void Game::Add(Arrow* arrow) {
    arrow->SetGame(this);
    arrows.push_back(arrow);
}

void Game::Remove(Arrow* arrow) {
    arrows.remove(arrow);
    delete arrow;
}

void Game::Loop() {
	while (!paused) {
		Update();
        CheckCollisions();
		Draw();
        tick++;
		Sleep(1000 / fps);
	}
}

void Game::Update() {
    PlayersList::iterator playerIterator;
    for (playerIterator = players.begin(); playerIterator != players.end(); playerIterator++) {
        (*playerIterator)->Update();
    }

    ArrowsList::iterator arrowIterator;
    for (arrowIterator = arrows.begin(); arrowIterator != arrows.end(); arrowIterator++) {
        (*arrowIterator)->Update();
    }
}

void Game::CheckCollisions() {
    Arrow* arrow;
    ArrowsList::iterator arrowIterator = arrows.begin();
    while (arrowIterator != arrows.end()) {
        arrow = *arrowIterator;
        if (arrow->GetHit()) {
            arrowIterator = arrows.erase(arrowIterator);
            delete arrow;
        } else {
            arrowIterator++;
        }
    }
}

void Game::Draw() {
	clrscr();

    WallsList::iterator wallIterator;
    for (wallIterator = walls.begin(); wallIterator != walls.end(); wallIterator++) {
        (*wallIterator)->Draw();
    }
    
	PlayersList::iterator playerIterator;
    for (playerIterator = players.begin(); playerIterator != players.end(); playerIterator++) {
        (*playerIterator)->Draw();
    }

    ArrowsList::iterator arrowIterator;
    for (arrowIterator = arrows.begin(); arrowIterator != arrows.end(); arrowIterator++) {
        (*arrowIterator)->Draw();
    }
}

int Game::GetTick() {
    return tick;
    }

Grid* Game::GetGrid() {
	return &grid;
}