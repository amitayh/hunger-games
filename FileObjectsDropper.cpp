#include "FileObjectsDropper.h"
#include "Game.h"
#include "Food.h"
#include "Quiver.h"
#include "Bomb.h"

using namespace HungerGames;

const char FileObjectsDropper::ACTION_FOOD      = 'f';
const char FileObjectsDropper::ACTION_QUIVER    = 'q';
const char FileObjectsDropper::ACTION_BOMB      = 'b';

FileObjectsDropper::FileObjectsDropper(const char* filename): events(filename) {}

void FileObjectsDropper::drop(Game& game) {
    EventsFile::Event* ev = events.getEvent(game.getTick());
    if (ev) {
        list<char>& actions = ev->getActions();
        list<char>::iterator it = actions.begin();
        while (it != actions.end()) {
            switch (*it) {
                case ACTION_FOOD:
                    game.dropObject(new Food);
                    break;
                case ACTION_QUIVER:
                    game.dropObject(new Quiver);
                    break;
                case ACTION_BOMB:
                    game.dropObject(new Bomb);
                    break;
            }
            it++;
        }
    }
}