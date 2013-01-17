#include "FileObjectsDropper.h"
#include "Game.h"
#include "Food.h"
#include "Quiver.h"
#include "Bomb.h"

using namespace HungerGames;

const Action FileObjectsDropper::DROP_FOOD    = 'f';
const Action FileObjectsDropper::DROP_QUIVER  = 'q';
const Action FileObjectsDropper::DROP_BOMB    = 'b';

FileObjectsDropper::FileObjectsDropper(const char* filename): events(filename) {}

void FileObjectsDropper::drop(Game& game) {
    EventsFile::Event* ev = events.getEvent(game.getTick());
    if (ev) {
        ActionsList& actions = ev->getActions();
        ActionsList::iterator it = actions.begin();
        while (it != actions.end()) {
            DroppingObject* object = NULL;
            switch (*it) {
                case DROP_FOOD:
                    object = new Food;
                    break;
                case DROP_QUIVER:
                    object = new Quiver;
                    break;
                case DROP_BOMB:
                    object = new Bomb;
                    break;
            }
            if (object) {
                game.dropObject(*object);
            }
            ++it;
        }
    }
}