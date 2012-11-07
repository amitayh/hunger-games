#ifndef _PLAYER_H
#define _PLAYER_H

#include "MovingObject.h"

const int INITIAL_NUM_ARROWS = 3;
const int MIN_TICKS_BETWEEN_ARROWS = 3;
const int ARROW_PROBABILITY = 10;
const int CHANGE_DIRECTION_PROBABILITY = 0;

class Player : public MovingObject
{
	char name;
	int power;
    int remainingArrows;
    int lastArrowTick;

    void SetRandomDirection();
public:
	Player(char name, int power = 1000);

    void Update();
	void Draw();
    bool SetSquare(Square* square);
    void IncreasePower(int amount);
    void DecreasePower(int amount);
    void Battle(Player* otherPlayer);
    void ShootArrow();
    int GetPower();
};

#endif