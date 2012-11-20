#include "Game.h"
#include "MapLoader.h"

int main(int argc, char **argv) {
    Game game;
    MapLoader loader = MapLoader(&game);
    if (argc > 1 && loader.Load(argv[1])) {
        game.Run();
    } else {
        cout << "Unable to load map file" << endl;
    }

    return EXIT_SUCCESS;
}