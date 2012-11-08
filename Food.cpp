#include "Food.h"

void Food::Affect(Player* player) {
	DroppingObject::Affect(player);
	player->IncreasePower(200);
}

void Food::Draw() {
	GotoPosition();
	cout << '@';
}