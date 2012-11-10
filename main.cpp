#include "Game.h"
#include "MapLoader.h"
#include <time.h>

void main() {

    srand((unsigned int) time(NULL));

    Game game;

    MapLoader loader = MapLoader(&game);
    loader.Load("C:\\map.txt");

    game.Run();

}