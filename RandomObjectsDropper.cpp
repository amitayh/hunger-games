#include "RandomObjectsDropper.h"
#include "Common.h"
#include "Game.h"
#include "Food.h"
#include "Quiver.h"
#include "Bomb.h"

using namespace HungerGames;

const int RandomObjectsDropper::FOOD_PROBABILITY    = 2;
const int RandomObjectsDropper::QUIVER_PROBABILITY  = 2;
const int RandomObjectsDropper::BOMB_PROBABILITY    = 1;

void RandomObjectsDropper::drop(Game& game) {
    if (checkProbability(FOOD_PROBABILITY)) {
        game.dropObject(new Food);
    }
    if (checkProbability(QUIVER_PROBABILITY)) {
        game.dropObject(new Quiver);
    }
    if (checkProbability(BOMB_PROBABILITY)) {
        game.dropObject(new Bomb);
    }
}