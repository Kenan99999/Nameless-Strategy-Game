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
    EmptyCounter = 0;
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

bool IsMovingOkay (int FromTileSelected, int ToTileSelected, int PlayerID) {
                    IsTileOkay = 0;
                    int TroopCount = 0;
                    int EmptySlots = 0;
                    if(ToTileSelected) {
                        for(auto i : Tiles[ToTileSelected - 1]) {
                            if(i == FromTileSelected - 1) {
                                cout << i << " "  << FromTileSelected - 1 << endl;
                                IsTileOkay = 1;
                                break;
                            }
                        }
                        for(int i = 0; i < 10; ++i) {
                            if(Troops[ToTileSelected - 1][i].side == Players[PlayerID].color) {
                                TroopCount++;
                            }
                            if(Troops[ToTileSelected - 1][i].side == 'e') {
                                EmptySlots++;
                            }
                        }
                        if(TroopCount + MovingTroops.size() > 5 || EmptySlots < MovingTroops.size()) {
                            IsTileOkay = 0;
                        }
                    }
                    if(IsTileOkay) {
                        for(int i = 0; i < 10; ++i) {
                            if(Troops[ToTileSelected - 1][i].type == 'e') {
                                for(auto j : MovingTroops) {
                                    for(int k = 0; k < 10; ++k) {
                                        if(j.second.type == Troops[FromTileSelected - 1][k].type && j.second.side == Troops[FromTileSelected - 1][k].side && j.second.health == Troops[FromTileSelected - 1][k].health) {
                                            Troops[FromTileSelected - 1][k] = empty_troop;
                                            break;
                                        }
                                    }
                                    Troops[ToTileSelected - 1][i] = j.second;
                                    MovingTroopsCopy[j.first] = j.second;
                                    MovingTroops.erase(j.first);
                                    break;
                                }
                            }
                        }
                        Round++;
                        ToTileSelected = 0;
                        IsTileOkay = 1;
                        Checkbox = 0;
                        FromTileSelected = 0;
                        TileSelected = 0;
                        TroopChosen = 0;
                        Action = 0;
                        MovingTroop.type = 'n';
                        Key = 0;
                        Checkbox = 0;
                        PressedKeyM = 0;
                        PressedKeyP = 0;
                        PressedKeyC = 0;
                        MovingTroops.clear();
                        return true;
                    }
                    else {
                        cout << "You can't move troops more or less than 1 tile" << endl;
                        Checkbox = 0;
                        return false;
                    }
}

void DeleteEliminatedTroops() {
    for(int i = 0; i < PlayerCount; ++i) {
        if(Players[i].CommanderAvalible == 0) {
            for(int j = 0; j < 47; ++j) {
                for(int k = 0; k < 10; ++k) {
                    if(Troops[j][k].side == Players[i].color) {
                        Troops[j][k] = empty_troop;
                    }
                }
            }
        }
        else {
            continue;
        }
    }
}

bool DeleteTheTroop(int PlayerID, int Tile, int Slot) {
                if(Troops[Tile][Slot].side == 'e') {
                    cout << "That's an empty_troop slot!" << endl;
                    TroopChosen = 0;
                    return false;
                }
                else if(Troops[Tile][Slot].side != Players[PlayerID].color) {
                    cout << "You can't delete an enemy troop" << endl;
                    TroopChosen = 0;
                    return false;
                }
                else if(Troops[Tile][Slot].type == 'c') {
                    cout << "You can't delete your commander!" << endl;
                    TroopChosen = 0;
                    return false;
                }
                else if(Troops[Tile][Slot].side == Players[PlayerID].color) {
                    int First = 0;
                    int MaxHealth = 0;
                    switch(Troops[Tile][Slot].type) {
                        case 'i':
                            First = Infantry_Cost;
                            MaxHealth = Infantry_Full;
                            break;
                        case 'm':
                            First = Medic_Cost;
                            MaxHealth = Medic_Full;
                            break;
                        case 'a':
                            First = Artillery_Cost;
                            MaxHealth = Artillery_Full;
                            break;
                        case 't': 
                            First = Tank_Cost;
                            MaxHealth = Tank_Full;
                            break;
                        case 'p':
                            First = Plane_Cost;
                            MaxHealth = Plane_Full;
                        default:
                            break;
                    }
                    Players[PlayerID].WarPoints += (First * 6 / 10) * (Troops[Tile][Slot].health / MaxHealth);
                    PointDifferance = (First * 6 / 10) * (Troops[Tile][Slot].health / MaxHealth);
                    Troops[Tile][Slot] = empty_troop;
                    Round++;
                    TroopChosen = 0;
                    ItIsAnEmptySlot = 0;
                    Action = 0;
                    Checkbox = 0;
                    return true;
                }
                cout << "Unknown Error!" << endl;
                TroopChosen = 0;
                return false;
}

bool IsBuildOkay(int PlayerID, int Slot) {
            IsTileOkay = 0;
            for(int i = 0; i < 2; ++i) {
                if(Buildings[TileSelected - 1][i].type == 'e') {
                    IsTileOkay = 1;
                    Slot = i;
                    break;
                }
            }
            if(IsTileOkay) {
                IsTileOkay = 0;
                    for(int i = 0; i < 10; ++i) {
                        if(Troops[TileSelected - 1][i].side == Players[PlayerID].color) {
                            IsTileOkay = 1;
                            break;
                        }
                    }
                if(Players[PlayerID].WarPoints >= BuiltBuilding.cost && IsTileOkay) {
                    Buildings[TileSelected - 1][Slot] = BuiltBuilding;
                    Buildings[TileSelected - 1][Slot].WhoBuiltIt = Players[PlayerID].color;
                    Players[PlayerID].WarPoints -= BuiltBuilding.cost;
                    BoughtBuilding = 0;
                    TileSelected = 0;
                    Action = 0;
                    IsTileOkay = 1;
                    Round++;
                    return true;
                }
                else {
                    cout << "You don't have any troops on that tile or you don't have enough money" << endl;
                    return false;
                }
            }
            else {
                cout << "Tile is not okay!" << endl;
                return false;
            }
            return false;
}