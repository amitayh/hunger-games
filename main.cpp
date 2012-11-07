#include "Game.h"
#include "Wall.h"
#include "Player.h"
#include <time.h>

void main() {

    srand((unsigned int) time(NULL));

	Game game;

    Wall wall1, wall2, wall3, wall4, wall5, wall6,
         wall7, wall8, wall9, wall10, wall11, wall12,
         wall13, wall14, wall15, wall16, wall17, wall18;

	Player player1('A'), player2('B');

    game.AddObject(&wall1, 3, 5);
	game.AddObject(&wall2, 4, 5);
	game.AddObject(&wall3, 5, 5);
	game.AddObject(&wall4, 6, 5);
	game.AddObject(&wall5, 7, 5);
	game.AddObject(&wall6, 8, 5);

    game.AddObject(&wall7, 8, 50);
	game.AddObject(&wall8, 9, 50);
	game.AddObject(&wall9, 10, 50);
	game.AddObject(&wall10, 11, 50);
	game.AddObject(&wall11, 12, 50);
	game.AddObject(&wall12, 13, 50);

    game.AddObject(&wall13, 8, 44);
	game.AddObject(&wall14, 8, 45);
	game.AddObject(&wall15, 8, 46);
	game.AddObject(&wall16, 8, 47);
	game.AddObject(&wall17, 8, 48);
	game.AddObject(&wall18, 8, 49);

	game.AddObject(&player1, 10, 10);
    //game.Add(&player2, 20, 30);

	game.Run();

}