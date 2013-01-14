#include "Game.h"
#include "MapLoader.h"
#include <iostream>

using namespace std;
using namespace HungerGames;

int main(int argc, char* argv[]) {
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