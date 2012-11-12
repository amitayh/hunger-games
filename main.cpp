#include "Game.h"
#include "MapLoader.h"

void main() {
    Game game;
    MapLoader loader = MapLoader(&game);
    loader.Load("C:\\map.txt");
    game.Run();
}