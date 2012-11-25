#include "Game.h"
#include "MapLoader.h"

int main(int argc, char **argv) {
    Game game;
    MapLoader loader(game);
    if (argc > 1 && loader.load(argv[1])) {
        game.run();
    } else {
        cout << "Unable to load map file" << endl;
    }

    return EXIT_SUCCESS;
}