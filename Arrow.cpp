#include "Arrow.h"
#include "Game.h"
#include "Player.h"

Arrow::Arrow(Player *shooter, Square *square) {
    this->square = square;
    direction = shooter->GetDirection();
    hit = false;
}

Arrow::~Arrow() {
    square->Clear();
}

void Arrow::SetSquare(Square *square) {
    if (square->HasWall()) {
        hit = true;
    } else {
        this->square = square;
        CheckHit();
    }
}

void Arrow::Update(Game &game) {
    if (!CheckHit() && game.GetTick() % MOVE_INTERVAL == 0) {
        Square *nextSquare = GetNextSquare(game.GetGrid(), square, direction);
        square->Clear();
        SetSquare(nextSquare);
    }
}

bool Arrow::CheckHit() {
    if (square) {
        List &players = square->GetPlayers();
        if (!players.IsEmpty()) {
            // Hit first player on square
            Player *player = (Player *) players.Peek();
            player->DecreasePower(500);
            hit = true;
        }
    }
    return hit;
}

void Arrow::Draw() const {
    char ch;
    switch (direction) {
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
    square->Draw(ch, WHITE);
}

bool Arrow::GetHit() const {
    return hit;
}