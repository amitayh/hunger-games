#include "Arrow.h"
#include "Game.h"

Arrow::Arrow(Player* shooter) {
    this->shooter = shooter;
    SetDirection(shooter->GetDirection());
    SetSpeed(2);
    hit = false;
}

bool Arrow::SetSquare(Square* square) {
    if (square->GetWall()) {
        hit = true;
        return false;
    } else {
		MovingObject::SetSquare(square);
		return true;

		/*
		// Not here...
        PlayersList* players = square->GetPlayers();
        if (players->size()) {
            Player* player = players->front();
            if (player != shooter) {
                player->DecreasePower(500);
                hit = true;
                return false;
            }
        }
		*/
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