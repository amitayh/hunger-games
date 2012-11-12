#include "Menu.h"
#include "Game.h"
#include "Gotoxy.h"
#include <iostream>
#include <conio.h>

using namespace std;

MenuOption Menu::Choose() {
    clrscr();
    gotoxy(0, 0);

    cout << "Choose an option" << endl;
    cout << "----------------" << endl;
    cout << "1. Quit game" << endl;
    cout << "2. Resume" << endl;

    switch (_getch()) {
        case '1':   return QUIT;
        case '2':   return RESUME;
        default:    return Choose();
    }
}