#include "Game.h"

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