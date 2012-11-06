#include "Game.h"
#include <time.h>

void main() {

    srand((unsigned int) time(NULL));

	Game game;

    Wall wall1, wall2, wall3, wall4, wall5, wall6,
         wall7, wall8, wall9, wall10, wall11, wall12,
         wall13, wall14, wall15, wall16, wall17, wall18;

	Player player1('A'), player2('B');

    game.Add(&wall1, 3, 5);
	game.Add(&wall2, 4, 5);
	game.Add(&wall3, 5, 5);
	game.Add(&wall4, 6, 5);
	game.Add(&wall5, 7, 5);
	game.Add(&wall6, 8, 5);

    game.Add(&wall7, 8, 50);
	game.Add(&wall8, 9, 50);
	game.Add(&wall9, 10, 50);
	game.Add(&wall10, 11, 50);
	game.Add(&wall11, 12, 50);
	game.Add(&wall12, 13, 50);

    game.Add(&wall13, 8, 44);
	game.Add(&wall14, 8, 45);
	game.Add(&wall15, 8, 46);
	game.Add(&wall16, 8, 47);
	game.Add(&wall17, 8, 48);
	game.Add(&wall18, 8, 49);

	game.Add(&player1, 10, 10);
    //game.Add(&player2, 20, 30);

	game.Run();

}