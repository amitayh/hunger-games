#include "Menu.h"
#include "Console.h"
#include "Gotoxy.h"
#include <iostream>
#include <conio.h>

using namespace std;

Menu::Menu() {
    numOptions = 0;
}

Menu::~Menu() {
    for (int i = 0; i < numOptions; i++) {
        delete []options[i];
    }
}

bool Menu::AddOption(const char *option) {
    if (numOptions < MAX_OPTIONS) {
        options[numOptions] = strdup(option);
        numOptions++;
        return true;
    }
    return false;
}

int Menu::Choose() {
    clrscr();
    gotoxy(0, 0);
    ChangeColor(SILVER);

    cout << "Choose an option" << endl;
    cout << "----------------" << endl;
    
    for (int i = 0; i < numOptions; i++) {
        printf("%d. %s\n", i + 1, options[i]);
    }

    int option;
    do {
        option = getch() - '0';
    } while (option < 1 || option > numOptions);

    return option;
}