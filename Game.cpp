#include "Game.h"

Game::Game() {
    tick = 0;
	fps = FRAMES_PER_SECOND;
	grid.Init(DEFAULT_NUM_ROWS, DEFAULT_NUM_COLS);
}

void Game::AddObject(Object* object, int row, int col) {
    Square* square = grid.GetSquare(row, col);
    object->SetGame(this);
    object->SetSquare(square);
	objects.push_front(object);
}

void Game::RemoveObject(Object* object) {
    objects.remove(object);
    delete object;
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
		Draw();
        tick++;
		Sleep(1000 / fps);
	}
}

void Game::Update() {
	ObjectsListIterator it = objects.begin();
	while (it != objects.end()) {
        (*it)->Update();
        it++;
    }
}

void Game::Draw() {
	clrscr();
    ObjectsListIterator it = objects.begin();
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