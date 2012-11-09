#include "Game.h"
#include "Wall.h"
#include "Player.h"
#include <time.h>

void main() {

    srand((unsigned int) time(NULL));

    Game game;

    game.AddWall(3, 5);
    game.AddWall(4, 5);
    game.AddWall(5, 5);
    game.AddWall(6, 5);
    game.AddWall(7, 5);
    game.AddWall(8, 5);

    game.AddWall(8, 50);
    game.AddWall(9, 50);
    game.AddWall(10, 50);
    game.AddWall(11, 50);
    game.AddWall(12, 50);
    game.AddWall(13, 50);

    game.AddWall(8, 44);
    game.AddWall(8, 45);
    game.AddWall(8, 46);
    game.AddWall(8, 47);
    game.AddWall(8, 48);
    game.AddWall(8, 49);

    game.AddPlayer('A', 10, 10);
    game.AddPlayer('B', 10, 40);

    game.AddInfoBox(19, 1);

    game.Run();

}