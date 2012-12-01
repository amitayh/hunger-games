#include "InfoBox.h"
#include "Game.h"
#include "Player.h"
#include "Gotoxy.h"
#include <iostream>

using namespace std;

InfoBox::InfoBox(): size(WIDTH, HEIGHT) {}

void InfoBox::draw() const {
    List::Iterator it(pGame->getPlayers());
    int row = pSquare->getRow(),
        col = pSquare->getCol(),
        height = size.getHeight();

    changeColor(SILVER);
    
    gotoxy(col, row);
    cout << "P HP   A";
    gotoxy(col, row + 1);
    cout << "----------";

    for (int i = 2; i < height; i++) {
        gotoxy(col, row + i);
        if (!it.done()) {
            // Print player info
            List::Node* node = it.getCurrent();
            Player* player = (Player*) node->getData();
            printf("%c %-4d %-3d\n", player->getName(), player->getPower(), player->getRemainingArrows());
        } else {
            // Print empty line
            cout << "          ";
        }
    }
}

const Dimensions& InfoBox::getSize() const {
    return size;
}

bool InfoBox::inArea(const Grid::Square& square) const {
    if (pSquare) {
        int row = square.getRow(),
            col = square.getCol(),
            rowMin = pSquare->getRow(),
            rowMax = rowMin + size.getHeight(),
            colMin = pSquare->getCol(),
            colMax = colMin + size.getWidth();

        return (row >= rowMin && row <= rowMax && col >= colMin && col <= colMax);
    }
    return false;
}