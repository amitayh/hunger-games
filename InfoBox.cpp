#include "InfoBox.h"
#include "Game.h"
#include "Player.h"
#include "Gotoxy.h"
#include <iostream>

using namespace std;

InfoBox::InfoBox(): size(WIDTH, HEIGHT) {}

void InfoBox::setSquare(Grid::Square& square) {
    Object::setSquare(square);

    int width = size.getWidth(),
        height = size.getHeight(),
        row = square.getRow(),
        col = square.getCol();

    // Add walls around the info box
    for (int i = 0; i < width + 2; i++) {
        pGame->addWall(row - 1, col + i - 1);
        pGame->addWall(row + height, col + i - 1);
    }
    for (int i = 0; i < height; i++) {
        pGame->addWall(row + i, col - 1);
        pGame->addWall(row + i, col + width);
    }
}

void InfoBox::draw() const {
    List::Iterator it(pGame->getPlayers());
    int row = pSquare->getRow(),
        col = pSquare->getCol(),
        height = size.getHeight();

    changeColor(SILVER);
    
    gotoxy(col, row);
    cout << "HP   R E P";
    gotoxy(col, row + 1);
    cout << "----------";

    for (int i = 2; i < height; i++) {
        gotoxy(col, row + i);
        if (!it.done()) {
            // Print player info
            List::Node* node = it.getCurrent();
            Player* player = (Player*) node->getData();
            Player::ArrowsBag& arrowsBag = player->getArrowsBag();
            printf(
                "%4d%2d%2d%2d\n",
                player->getPower(),
                arrowsBag.getRemaining(Player::ArrowsBag::REGULAR),
                arrowsBag.getRemaining(Player::ArrowsBag::EXPLODING),
                arrowsBag.getRemaining(Player::ArrowsBag::PENETRATING)
            );
        } else {
            // Print empty line
            cout << "          ";
        }
    }
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