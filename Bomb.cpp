#include "Bomb.h"

void Bomb::Affect(Player* player) {
    DroppingObject::Affect(player);
    player->DecreasePower(750);
}

void Bomb::Draw() {
    GotoPosition();
    ChangeColor(Color::RED);
    cout << '@';
}