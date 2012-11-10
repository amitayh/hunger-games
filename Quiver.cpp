#include "Quiver.h"

void Quiver::Affect(Player* player) {
    DroppingObject::Affect(player);
    player->AddArrows(3);
}

void Quiver::Draw() {
    GotoPosition();
    ChangeColor(Color::YELLOW);
    cout << '*';
}