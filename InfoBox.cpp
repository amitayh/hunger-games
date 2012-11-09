#include "InfoBox.h"
#include "Game.h"
#include "Player.h"

InfoBox::InfoBox() {
    Dimensions* size = GetSize();
    size->Set(10, 5);
}

void InfoBox::Draw() {
    Player* player;
    Game* game = GetGame();
    Square* square = GetSquare();
    PlayersList* players = game->GetPlayers();
    PlayersIterator it = players->begin();
    Dimensions* size = GetSize();
    int row = square->GetRow(), col = square->GetCol();
    
    gotoxy(col, row);
    cout << "P Pwr  Ars";
    gotoxy(col, row + 1);
    cout << "----------";

    for (int i = 2; i < size->GetHeight() && it != players->end(); i++, it++) {
        player = *it;
        gotoxy(square->GetCol(), square->GetRow() + i);
        printf("%c %-4d %-3d\n", player->GetName(), player->GetPower(), player->GetRemainingArrows());
    }
}