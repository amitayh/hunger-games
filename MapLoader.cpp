#include "MapLoader.h"
#include <fstream>

MapLoader::MapLoader(Game &game) {
    pGame = &game;
}

bool MapLoader::Load(const string &filename) {
    ifstream map(filename);
    if (map.good()) {
        Grid &grid = pGame->GetGrid();
        int rows = grid.GetRows(),
            cols = grid.GetCols();

        int players = 0;
        bool addedInfoBox = false;

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (map.eof()) {
                    // Oops! Something went wrong...
                    return false;
                }
                switch (map.get()) {
                    case CHAR_WALL:
                        pGame->AddWall(row, col);
                        break;
                    case CHAR_PLAYER:
                        pGame->AddPlayer(row, col);
                        players++;
                        break;
                    case CHAR_INFO_BOX:
                        if (!addedInfoBox) {
                            pGame->AddInfoBox(row, col);
                            addedInfoBox = true;
                        }
                        break;
                }
            }
            map.get(); // Consume linebreak
        }

        // Add additional players if needed
        for (int i = players; i < MIN_NUM_PLAYERS; i++) {
            pGame->AddPlayer(pGame->GetValidDropSquare());
        }

        map.close(); // Close map file
        return true; // Success - map loaded
    }
    return false; // Unable to open map file
}