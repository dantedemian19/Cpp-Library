#pragma once
#include "include.h"

void pause() {
    int cha = 0;
    cout << "\t pulse a enter to continue";
    while (cha != 13) {
        cha = _getch();
    }
};
void cls() {
    cout << "\033c";
};
void wait(int time = 2) {// hace esperar al usuario 2 segundos
    time *= 1000;
    int passed = 0;
    int i = 0;
    cout << "\t loading";
    while (passed < time) {
        Sleep(200);
        passed += 200;
        cout << ".";
        i += 1;
        if (i > 5) { i = 0;  cls(); cout << "\t loading"; }
    }
};
void errormens() {
    cout << " an error was ocurred, please be alarmed and run to a safe place  \n"; // not an easter egg
};