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

int Menu::addOption(const char* option) {
    if (numOptions < MAX_OPTIONS) {
        // Add the option and return its number
        options[numOptions] = strdup(option);
        numOptions++;
        return numOptions;
    }
    return 0;
}

void Menu::show() const {
    clrscr();
    gotoxy(0, 0);
    changeColor(SILVER);

    cout << "Choose an option" << endl;
    cout << "----------------" << endl;
    
    // Print options
    for (int i = 0; i < numOptions; i++) {
        cout << (i + 1) << ". " << options[i] << endl;
    }
}

int Menu::choose() const {
    show();

    int option;
    do {
        // Get a valid input from user
        option = getch() - '0';
    } while (option < 1 || option > numOptions);

    return option;
}