#include "MapLoader.h"
#include "Common.h"
#include "Game.h"
#include "Bot.h"
#include "ScheduledPlayer.h"
#include "Human.h"
#include "FileObjectsDropper.h"
#include "RandomObjectsDropper.h"
#include <fstream>

using namespace HungerGames;

const char  MapLoader::CHAR_WALL                = 'W';
const char  MapLoader::CHAR_BOT                 = 'P';
const char  MapLoader::CHAR_HUMAN_PLAYER        = 'H';
const char  MapLoader::CHAR_SCHEDULED_PLAYER    = 'C';
const char  MapLoader::CHAR_INFO_BOX            = 'O';
const char  MapLoader::CHAR_EVENTS_FILE         = 'E';
const int   MapLoader::MIN_NUM_PLAYERS          = 2;
const int   MapLoader::MAX_NUM_PLAYERS          = 3;
const Console::Color MapLoader::PLAYER_COLORS[] = {
    Console::CYAN, Console::MAGENTA, Console::YELLOW
};

MapLoader::MapLoader(Game& game) {
    pGame = &game;
}

void MapLoader::loadFromArguments(int argc, char* argv[]) const {
    char* mapFile = NULL;
    char* eventsFile = NULL;
    char* scheduledPlayersFiles[MAX_NUM_PLAYERS] = {NULL};
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == CHAR_SCHEDULED_PLAYER && argv[i][2] == '=') {
            // Player's instructions file
            int index = (argv[i][1] - '0') - 1; // Convert second char to index
            if (index >= 0 && index < MAX_NUM_PLAYERS) {
                scheduledPlayersFiles[index] = argv[i] + 3; // Skip 'C1='
            }
        } else if (argv[i][0] == CHAR_EVENTS_FILE && argv[i][1] == '=') {
            // Events file
            eventsFile = argv[i] + 2; // Skip 'E='
        } else {
            // Default - map file
            mapFile = argv[i];
        }
    }
    if (!mapFile) {
        throw invalid_argument("Map file was not provided");
    }
    load(mapFile, eventsFile, scheduledPlayersFiles);
}

void MapLoader::load(const char* mapFile, const char* eventsFile, char* scheduledPlayersFiles[]) const {
    ifstream map(mapFile);
    if (!map.good()) {
        throw IOError("Unable to open map file");
    }

    PlayersList& players = pGame->getPlayers();
    const Grid& grid = pGame->getGrid();
    int rows = grid.getRows(), cols = grid.getCols();

    bool addedInfoBox = false; // Info box flag
    bool addedHumanPlayer = false; // Human player flag
    int scheduled = 0; // Scheduled players counter
    int bots = 0; // Bots counter

    try {
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (map.eof()) {
                    throw EndOfFile("Map file ended unexpectedly");
                }
                switch (map.get()) {
                    case CHAR_WALL:
                        pGame->addWall(row, col);
                        break;
                    case CHAR_BOT:
                        if (players.size() < MAX_NUM_PLAYERS && pGame->isValidDrop(row, col)) {
                            char name = 'A' + bots + scheduled; // Name the bots sequentially (A, B, C...)
                            Console::Color color = getPlayerColor();
                            Bot* bot = new Bot(name, color);
                            pGame->addPlayer(bot, row, col);
                            bots++;
                        }
                        break;
                    case CHAR_SCHEDULED_PLAYER:
                        if (players.size() < MAX_NUM_PLAYERS && pGame->isValidDrop(row, col)) {
                            char name = 'A' + bots + scheduled;
                            Console::Color color = getPlayerColor();
                            char* scheduledPlayersFile = scheduledPlayersFiles[scheduled];
                            if (!scheduledPlayersFile) {
                                throw invalid_argument("No events file was provided for scheduled player");
                            }
                            ScheduledPlayer* player = new ScheduledPlayer(name, color, scheduledPlayersFile);
                            pGame->addPlayer(player, row, col);
                            scheduled++;
                        }
                        break;
                    case CHAR_HUMAN_PLAYER:
                        if (!addedHumanPlayer && players.size() < MAX_NUM_PLAYERS && pGame->isValidDrop(row, col)) {
                            Console::Color color = getPlayerColor();
                            HumanPlayer* human = new HumanPlayer(CHAR_HUMAN_PLAYER, color);
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
        map.close(); // Close map file
    } catch (const exception& e) {
        map.close(); // Close map file before throwing the exception
        throw e;
    }

    // Add additional bots if needed
    for (int i = players.size(); i < MIN_NUM_PLAYERS; i++) {
        char name = 'A' + bots + scheduled;
        Console::Color color = getPlayerColor();
        Bot* bot = new Bot(name, color);
        Grid::Square& square = pGame->getValidDropSquare();
        pGame->addPlayer(bot, square);
        bots++;
    }

    if (eventsFile) {
        // Events file objects dropper
        pGame->setObjectsDropper(new FileObjectsDropper(eventsFile));
    } else {
        // Default objects dropper
        pGame->setObjectsDropper(new RandomObjectsDropper);
    }
}

Console::Color MapLoader::getPlayerColor() const {
    return PLAYER_COLORS[pGame->getPlayers().size() % 3];
}