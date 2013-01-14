#include "FileObjectsDropper.h"
#include "Game.h"
#include "Food.h"
#include "Quiver.h"
#include "Bomb.h"

using namespace HungerGames;

const char FileObjectsDropper::FOOD_ACTION      = 'f';
const char FileObjectsDropper::QUIVER_ACTION    = 'q';
const char FileObjectsDropper::BOMB_ACTION      = 'b';

FileObjectsDropper::FileObjectsDropper(const char* filename): events(filename) {}

void FileObjectsDropper::drop(Game& game) {
    EventsFile::Event* ev = events.getEvent(game.getTick());
    if (ev) {
        list<char>& actions = ev->getActions();
        list<char>::iterator it = actions.begin();
        while (it != actions.end()) {
            switch (*it) {
                case FOOD_ACTION:
                    game.dropObject(new Food);
                    break;
                case QUIVER_ACTION:
                    game.dropObject(new Quiver);
                    break;
                case BOMB_ACTION:
                    game.dropObject(new Bomb);
                    break;
            }
            it++;
        }
    }
}