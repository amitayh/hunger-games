#include "Arrow.h"
#include "Game.h"

Arrow::Arrow() {
	SetMoveInterval(1);
    hit = false;
}

void Arrow::SetSquare(Square* square) {
    if (square->GetWall()) {
        hit = true;
    } else {
		PlayersList* players = square->GetPlayers();
        if (players->size()) {
            Player* player = players->front();
            //if (player != shooter) {
                player->DecreasePower(500);
                hit = true;
            //}
        }

		MovingObject::SetSquare(square);
	}
}

bool Arrow::Update() {
    MovingObject::Update();
    return !hit;
}

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