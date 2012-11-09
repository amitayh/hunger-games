#include "Game.h"
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
	if (square->IsEmpty()) {
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

int Game::GetTick() {
    return tick;
}

Grid* Game::GetGrid() {
	return &grid;
}