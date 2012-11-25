#include "MapLoader.h"
#include <fstream>

MapLoader::MapLoader(Game& game) {
    pGame = &game;
}

bool MapLoader::load(const string& filename) const {
    ifstream map(filename);
    if (map.good()) {
        const Grid& grid = pGame->getGrid();
        int rows = grid.getRows(),
            cols = grid.getCols();

        int players = 0; // Players counter
        bool addedInfoBox = false; // Info box flag

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (map.eof()) {
                    // Oops! Something went wrong...
                    map.close();
                    return false;
                }
                switch (map.get()) {
                    case CHAR_WALL:
                        pGame->addWall(row, col);
                        break;
                    case CHAR_PLAYER:
                        if (pGame->isValidDrop(row, col)) {
                            pGame->addPlayer(row, col);
                            players++;
                        }
                        break;
                    case CHAR_INFO_BOX:
                        if (!addedInfoBox) {
                            pGame->addInfoBox(row, col);
                            addedInfoBox = true;
                        }
                        break;
                }
            }
            map.get(); // Consume linebreak
        }

        // Add additional players if needed
        for (int i = players; i < MIN_NUM_PLAYERS; i++) {
            pGame->addPlayer(pGame->getValidDropSquare());
        }

        map.close(); // Close map file
        return true; // Success - map loaded
    }
    return false; // Unable to open map file
}