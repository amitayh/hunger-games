#include "MapLoader.h"
#include <fstream>

MapLoader::MapLoader(Game* game) {
    this->game = game;
}

bool MapLoader::Load(const char* filename) {
    ifstream map(filename);
    if (map.good()) {
        Grid* grid = game->GetGrid();
        int rows = grid->GetRows(),
            cols = grid->GetCols();

        int players = 0;
        bool addedInfoBox = false;

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                switch (map.get()) {
                    case CHAR_WALL:
                        game->AddWall(row, col);
                        break;
                    case CHAR_PLAYER:
                        game->AddPlayer(row, col);
                        players++;
                        break;
                    case CHAR_INFO_BOX:
                        if (!addedInfoBox) {
                            game->AddInfoBox(row, col);
                            addedInfoBox = true;
                        }
                        break;
                }
            }
            map.get(); // Consume linebreak
        }

        // Add additional players if needed
        for (int i = players; i < MIN_NUM_PLAYERS; i++) {
            Square* square = game->GetValidDropSquare();
            game->AddPlayer(square);
        }

        map.close();
        return true;
    }
    return false;
}