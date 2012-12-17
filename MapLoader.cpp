#include "MapLoader.h"
#include "Game.h"
#include "Bot.h"
#include <fstream>

const char  MapLoader::CHAR_WALL        = 'W';
const char  MapLoader::CHAR_BOT         = 'P';
const char  MapLoader::CHAR_HUMAN       = 'H';
const char  MapLoader::CHAR_INFO_BOX    = 'O';
const int   MapLoader::MIN_NUM_PLAYERS  = 2;
const int   MapLoader::MAX_NUM_PLAYERS  = 3;

MapLoader::MapLoader(Game& game) {
    pGame = &game;
}

bool MapLoader::load(const string& filename) const {
    ifstream map(filename);
    if (map.good()) {
        ObjectsList& players = pGame->getPlayers();
        const Grid& grid = pGame->getGrid();
        int rows = grid.getRows(), cols = grid.getCols();

        bool addedInfoBox = false; // Info box flag
        bool addedHumanPlayer = false; // Human player flag
        int bots = 0; // Bots counter

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
                    case CHAR_BOT:
                        if (players.size() < MAX_NUM_PLAYERS && pGame->isValidDrop(row, col)) {
                            char name = 'A' + bots; // Name the bots sequentially (A, B, C...)
                            pGame->addBot(new Bot(name), row, col);
                            bots++;
                        }
                        break;
                    case CHAR_HUMAN:
                        if (!addedHumanPlayer && players.size() < MAX_NUM_PLAYERS && pGame->isValidDrop(row, col)) {
                            pGame->addHuman(row, col);
                            addedHumanPlayer = true;
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

        // Add additional bots if needed
        for (int i = players.size(); i < MIN_NUM_PLAYERS; i++) {
            char name = 'A' + bots;
            pGame->addBot(new Bot(name), pGame->getValidDropSquare());
            bots++;
        }

        map.close(); // Close map file
        return true; // Success - map loaded
    }
    return false; // Unable to open map file
}