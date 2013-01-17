#include "Game.h"
#include "MapLoader.h"
#include <time.h>
#include <iostream>

using namespace std;
using namespace HungerGames;

int main(int argc, char* argv[]) {
    // Initialize random number generator
    srand((unsigned int) time(NULL));

    Game game;
    MapLoader loader(game);

    try {
        loader.loadFromArguments(argc, argv);
        game.run();
    } catch (const exception& e) {
        cerr << e.what() << endl;
    } catch (...) {
        cerr << "An error occurred" << endl;
    }

    return EXIT_SUCCESS;
}