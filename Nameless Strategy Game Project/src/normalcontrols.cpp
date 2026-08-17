#include "functions.h"
#include "globals.h"
#include <bits/stdc++.h>
#include <raylib.h>
using namespace std;

void ClearMouseCoords() {
    MouseX = 0;
    MouseY = 0;
    return;
}

void IncreaseWarPoints() {
    int r;
    for(int i = 0; i < PlayerCount; ++i) {
        r = rand();
        Players[i].WarPoints += (r % 2 + 2) + (Round / 100);
    }
    Increased = 1;
    return;
}

void GetMouseCoords() {
    MouseX = GetMouseX();
    MouseY = GetMouseY();
    return;
}

