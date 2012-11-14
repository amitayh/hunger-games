#include "Game.h"
#include "MapLoader.h"

void main() {
    Game game;
    MapLoader loader = MapLoader(&game);
    if (loader.Load("C:\\map.txt")) {
        game.Run();
    } else {
        cout << "Unable to load map file" << endl;
    }
}