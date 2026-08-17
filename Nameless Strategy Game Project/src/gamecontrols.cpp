#include "functions.h"
#include "globals.h"
#include <bits/stdc++.h>

using namespace std;

bool IsCommanderPlacementOkay(int Tile, char Gamer) {
    if(Troops[Tile - 1][0].type != 'e' || Tile > 47) {
        if(Tile > 47) cout << "Commander can't swim!" << endl;
        cout << "can't place a commander on enemy tile!" << endl;
        return false;
    }
    Troops[Tile - 1][0] = commander;
    Troops[Tile - 1][0].side = Gamer;
    Round++;
    return true;
}

