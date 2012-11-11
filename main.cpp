#include "Game.h"
#include "MapLoader.h"

/*
void main() {
    Game game;

    game.AddWall(1, 5);
    game.AddWall(2, 5);
    game.AddWall(3, 5);
    //game.AddWall(5, 15);

    game.AddPlayer(5, 5);

    game.Run();
}
*/

void main() {
    Game game;
    MapLoader loader = MapLoader(&game);
    loader.Load("C:\\map.txt");
    game.Run();
}