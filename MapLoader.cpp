#include "MapLoader.h"
#include <stdio.h>

MapLoader::MapLoader(Game* game) {
    this->game = game;
}

bool MapLoader::Load(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp) {
        Grid* grid = game->GetGrid();
        int rows = grid->GetRows(),
            cols = grid->GetCols();

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                switch (fgetc(fp)) {
                    case CHAR_WALL:
                        game->AddWall(row, col);
                        break;
                    case CHAR_PLAYER:
                        game->AddPlayer(row, col);
                        break;
                    case CHAR_INFO_BOX:
                        game->AddInfoBox(row, col);
                        break;
                }
            }
            fgetc(fp); // Consume linebreak
        }

        fclose(fp);
        return true;
    }
    return false;
}