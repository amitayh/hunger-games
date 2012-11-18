#include "InfoBox.h"
#include "Game.h"
#include "Player.h"

InfoBox::InfoBox() {
    Dimensions* size = GetSize();
    size->SetWidth(10);
    size->SetHeight(5);
}

void InfoBox::Draw() {
    Game* game = GetGame();
    Square* square = GetSquare();
    List* players = game->GetPlayers();
    ListIterator it(players);
    Dimensions* size = GetSize();
    int row = square->GetRow(), col = square->GetCol();

    ChangeColor(SILVER);
    
    gotoxy(col, row);
    cout << "P HP   A";
    gotoxy(col, row + 1);
    cout << "----------";

    for (int i = 2; i < size->GetHeight(); i++) {
        gotoxy(col, row + i);
        if (!it.Done()) {
            // Print player info
            ListNode* node = it.Current();
            Player* player = (Player*) node->GetData();
            printf("%c %-4d %-3d\n", player->GetName(), player->GetPower(), player->GetRemainingArrows());
        } else {
            // Print empty line
            cout << "          ";
        }
    }
}