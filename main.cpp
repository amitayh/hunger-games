#include "Game.h"
#include "Wall.h"
#include "Player.h"
#include <time.h>

void main() {

    srand((unsigned int) time(NULL));

	Game game;

    game.AddObject(new Wall, 3, 5);
	game.AddObject(new Wall, 4, 5);
	game.AddObject(new Wall, 5, 5);
	game.AddObject(new Wall, 6, 5);
	game.AddObject(new Wall, 7, 5);
	game.AddObject(new Wall, 8, 5);

    game.AddObject(new Wall, 8, 50);
	game.AddObject(new Wall, 9, 50);
	game.AddObject(new Wall, 10, 50);
	game.AddObject(new Wall, 11, 50);
	game.AddObject(new Wall, 12, 50);
	game.AddObject(new Wall, 13, 50);

    game.AddObject(new Wall, 8, 44);
	game.AddObject(new Wall, 8, 45);
	game.AddObject(new Wall, 8, 46);
	game.AddObject(new Wall, 8, 47);
	game.AddObject(new Wall, 8, 48);
	game.AddObject(new Wall, 8, 49);

	game.AddObject(new Player('A'), 10, 10);
    game.AddObject(new Player('B'), 10, 40);

	game.Run();

}