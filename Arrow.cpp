#include "Arrow.h"
#include "Game.h"

Arrow::Arrow(Player* shooter) {
    SetType(ARROW);
    this->shooter = shooter;
    SetDirection(shooter->GetDirection());
    SetSpeed(2);
    //hit = false;
}

/*
bool Arrow::SetSquare(Square* square) {
    if (square->IsOccupied()) {
        // Check objects on square
        ObjectsList* objects = square->GetObjects();
        ObjectsList::iterator iterator;
        ObjectType type;
        for (iterator = objects->begin(); !hit && iterator != objects->end(); iterator++) {
            type = (*iterator)->GetType();
            if (type == WALL || type == PLAYER) {
                hit = true;
            }
        }
		if (hit) {
			return false;
		}
    }
    return MovingObject::SetSquare(square);
}

/*
void Arrow::Update() {
    MovingObject::Update();
    if (hit) {
        Game* game = GetGame();
        game->Remove(this);
    }
}
*/

void Arrow::Draw() {
    char ch;
    switch (GetDirection()) {
        case UP:
            ch = '^';
            break;
        case DOWN:
            ch = 'v';
            break;
        case LEFT:
            ch = '<';
            break;
        case RIGHT:
            ch = '>';
            break;
    }

    GotoPosition();
    cout << ch;
}

/*
bool Arrow::GetHit() {
    return hit;
}
*/