#include "functions.h"
#include "globals.h"
#include <bits/stdc++.h>

using namespace std;

bool IsCommanderPlacementOkay(int Tile, int PlayerID) {
    if(Troops[Tile - 1][0].type != 'e' || Tile > 47) {
        if(Tile > 47) cout << "Commander can't swim!" << endl;
        cout << "can't place a commander on enemy tile!" << endl;
        return false;
    }
    Troops[Tile - 1][0] = commander;
    Troops[Tile - 1][0].side = Players[PlayerID - 1].color;
    Round++;
    return true;
}

bool IsPlacementOkay(int Tile, int PlayerID) {
    int TroopCount = 0;
    int EmptyCounter = 0;
    int IsCommanderHere = 0;
    int IsTileOkay = 1;
    for(int i = 0; i < 10; ++i) {
        if(Troops[Tile - 1][i].type != 'e' && Troops[Tile - 1][i].side != Players[PlayerID].color) {
            IsTileOkay = 0;
        }
        if(Troops[Tile - 1][i].side == Players[PlayerID].color && Troops[Tile - 1][i].type == 'c') {
            IsCommanderHere = 1;
        }
        if(Troops[Tile - 1][i].side == Players[PlayerID].color) {
            TroopCount++;
        }
        else if(Troops[Tile - 1][i].type == 'e' && !EmptyCounter) {
            EmptyCounter = i + 1;
        }
    }
    if(TroopCount >= 5) {
        IsTileOkay = 0;
        IsCommanderHere = 0;
    }
    if(!EmptyCounter) {
        IsTileOkay = 0;
        IsCommanderHere = 0;
    }
    if(IsTileOkay || IsCommanderHere) {
        Troops[Tile - 1][EmptyCounter - 1] = Players[PlayerID].TroopBank[Key - 1];
        Players[PlayerID].TroopBank[Key - 1] = empty_troop;
        cout << "a(n) " << Troops[Tile - 1][EmptyCounter - 1].type << " troop succesfully placed" << endl;
        Round++;
        Action = 0;
        PressedKeyC = 0;
        PressedKeyP = 0;
        PressedKeyM = 0;
        Checkbox = 0;
        TempKey = 0;
        TroopChosen = 0;
        Key = 0;
        TileSelected = 0;
        return true;
    }
    else {
        cout << "Tile is either occupied by the enemy or doesn't have any empty_troop slots" << endl;
        Checkbox = 0;
        return false;
    }
}

bool AddBoughtTroopToTheTroopBank(int Troop, int PlayerID) {
        for(int i = 0; i < 10; ++i) {
            if(Players[PlayerID].TroopBank[i].type == empty_troop.type) {
                switch(Troop) {
                    case 1:
                        Players[PlayerID].WarPoints -= Infantry_Cost;
                        if(Players[PlayerID].WarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            Players[PlayerID].WarPoints += Infantry_Cost;
                            return false;
                        }
                        Players[PlayerID].TroopBank[i] = infantry;
                        Players[PlayerID].TroopBank[i].side = Players[PlayerID].color;

                        break;
                    case 2:
                        Players[PlayerID].WarPoints -= Medic_Cost;
                        if(Players[PlayerID].WarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            Players[PlayerID].WarPoints += Medic_Cost;
                            return false;
                        }
                        Players[PlayerID].TroopBank[i] = medic;
                        Players[PlayerID].TroopBank[i].side = Players[PlayerID].color;

                        break;
                    case 3:
                        Players[PlayerID].WarPoints -= Artillery_Cost;
                        if(Players[PlayerID].WarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            Players[PlayerID].WarPoints += Artillery_Cost;
                            return false;
                        }
                        Players[PlayerID].TroopBank[i] = artillery;
                        Players[PlayerID].TroopBank[i].side = Players[PlayerID].color;

                        break;
                    case 4:
                        Players[PlayerID].WarPoints -= Tank_Cost;
                        if(Players[PlayerID].WarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            Players[PlayerID].WarPoints += Tank_Cost;
                            return false;
                        }
                        Players[PlayerID].TroopBank[i] = tank;
                        Players[PlayerID].TroopBank[i].side = Players[PlayerID].color;

                        break;
                    case 5:
                        Players[PlayerID].WarPoints -= Plane_Cost;
                        if(Players[PlayerID].WarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            Players[PlayerID].WarPoints += Plane_Cost;
                            return false;
                        }
                        Players[PlayerID].TroopBank[i] = plane;
                        Players[PlayerID].TroopBank[i].side = Players[PlayerID].color;

                        break;
                    default:
                        break;
                }
                cout << "Bought troop added to slot " << i << endl;
                Round++;
                return true;
            }
        }
        cout << "There are no empty_troop spaces for another troop!" << endl;
        Troop = 0;
        Action = 0;
        return false;
}

void DeleteEliminatedTroops(int PlayerCount) {
    for(int i = 0; i < PlayerCount; ++i) {
        if(Players[i].CommanderAvalible) {
            continue;
        }
        for(int j = 0; j < 47; ++j) {
            for(int k = 0; k < 10; ++k) {
                if(Troops[j][k].side == Players[i].color) {
                    Troops[j][k] = empty_troop;
                }
            }
        }
    }
}

