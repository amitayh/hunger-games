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
        MovingObject::SetSquare(square);
        CheckHit();
    }
}

void Arrow::Update() {
    if (!CheckHit()) {
        MovingObject::Update();
    }
}

bool Arrow::CheckHit() {
    Square* square = GetSquare();
    if (square) {
        PlayersList* players = square->GetPlayers();
        if (!players->empty()) {
            Player* player = players->front();
            player->DecreasePower(500);
            hit = true;
        }
    }
    return hit;
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
    ChangeColor(WHITE);
    cout << ch;
}

bool Arrow::GetHit() {
    return hit;
}