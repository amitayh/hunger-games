#include "InfoArea.h"
#include "Game.h"

InfoArea::InfoArea() {
    Dimensions* size = GetSize();
    size->Set(10, 5);
}

void InfoArea::Draw() {
	Game* game = GetGame();
	//PlayersList* game->GetPlayers();
}