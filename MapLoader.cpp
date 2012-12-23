#include "MapLoader.h"
#include "Game.h"
#include "Bot.h"
#include "Human.h"
#include <fstream>

using namespace HungerGames;

const Console::Color MapLoader::PLAYER_COLORS[3] = {
    Console::CYAN, Console::MAGENTA, Console::YELLOW
};

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
                            Console::Color color = getPlayerColor();
                            Bot* bot = new Bot(name, color);
                            pGame->addPlayer(bot, row, col);
                            bots++;
                        }
                        break;
                    case CHAR_HUMAN:
                        if (!addedHumanPlayer && players.size() < MAX_NUM_PLAYERS && pGame->isValidDrop(row, col)) {
                            Console::Color color = getPlayerColor();
                            Human* human = new Human(CHAR_HUMAN, color);
                            pGame->addPlayer(human, row, col);
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
            Console::Color color = getPlayerColor();
            Bot* bot = new Bot(name, color);
            Grid::Square& square = pGame->getValidDropSquare();
            pGame->addPlayer(bot, square);
            bots++;
        }

        map.close(); // Close map file
        return true; // Success - map loaded
    }
    return false; // Unable to open map file
}

Console::Color MapLoader::getPlayerColor() const {
    return PLAYER_COLORS[pGame->getPlayers().size() % 3];
}