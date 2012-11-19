#include "InfoBox.h"
#include "Player.h"
#include "Gotoxy.h"
#include <iostream>

using namespace std;

InfoBox::InfoBox(): size(WIDTH, HEIGHT) {}

void InfoBox::SetSquare(Square *square) {
    this->square = square;
}

void InfoBox::Draw(List *players) const {
    ListIterator it(players);
    int row = square->GetRow(), col = square->GetCol();

    ChangeColor(SILVER);
    
    gotoxy(col, row);
    cout << "P HP   A";
    gotoxy(col, row + 1);
    cout << "----------";

    for (int i = 2; i < size.GetHeight(); i++) {
        gotoxy(col, row + i);
        if (!it.Done()) {
            // Print player info
            ListNode *node = it.Current();
            Player *player = (Player *) node->GetData();
            printf("%c %-4d %-3d\n", player->GetName(), player->GetPower(), player->GetRemainingArrows());
        } else {
            // Print empty line
            cout << "          ";
        }
    }
}

const Dimensions& InfoBox::GetSize() const {
    return size;
}

bool InfoBox::InArea(const Square *square) const {
    int row = square->GetRow(),
        col = square->GetCol(),
        rowMin = this->square->GetRow(),
        rowMax = rowMin + size.GetHeight(),
        colMin = this->square->GetCol(),
        colMax = colMin + size.GetWidth();

    return (row >= rowMin && row <= rowMax && col >= colMin && col <= colMax);
}