#include "InfoBox.h"
#include "Game.h"
#include "Player.h"

InfoBox::InfoBox() {
    Dimensions* size = GetSize();
    size->SetWidth(10);
    size->SetHeight(5);
}

void InfoBox::Draw() {
    Player* player;
    Game* game = GetGame();
    Square* square = GetSquare();
    PlayersList* players = game->GetPlayers();
    PlayersIterator it = players->begin();
    Dimensions* size = GetSize();
    int row = square->GetRow(), col = square->GetCol();

    ChangeColor(SILVER);
    
    gotoxy(col, row);
    cout << "P HP   A";
    gotoxy(col, row + 1);
    cout << "----------";

    for (int i = 2; i < size->GetHeight(); i++) {
        gotoxy(square->GetCol(), square->GetRow() + i);
        if (it != players->end()) {
            player = *it;
            printf("%c %-4d %-3d\n", player->GetName(), player->GetPower(), player->GetRemainingArrows());
            it++;
        } else {
            cout << "          ";
        }
    }
}