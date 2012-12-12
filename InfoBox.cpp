#include "InfoBox.h"
#include "Game.h"
#include "Player.h"
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
    ObjectsList& players = pGame->getPlayers();
    ObjectsIterator it = players.begin();
    int row = pSquare->getRow(),
        col = pSquare->getCol(),
        height = size.getHeight();

    Console::changeColor(Console::SILVER);
    
    Console::gotoPosition(row, col);
    cout << "HP   > * -";
    Console::gotoPosition(row + 1, col);
    cout << "----------";

    for (int i = 2; i < height; i++) {
        Console::gotoPosition(row + i, col);
        if (it != players.end()) {
            // Print player info
            Player* player = (Player*) *it;
            cout << *player;
            it++;
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