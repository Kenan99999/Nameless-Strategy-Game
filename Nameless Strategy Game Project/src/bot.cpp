#include <bits/stdc++.h>
#include "globals.h"



// Build ekle
 void BotMove() {
    bool MoveMade = 0;
    int Move = 0;
    while(!MoveMade) {
        Move = GetRandomValue(1, 5); // 1: Buy 2: Place 3: Move 4: Delete 5: SkipRound 6:Build (not added)
        if(Round == 1) {
            int BotCommander = GetRandomValue(1, 47);
            if(Troops[BotCommander - 1][0].type == 'e') {
                Troops[BotCommander - 1][0] = commander;
                Troops[BotCommander - 1][0].side = 'b';
                MoveMade = 1;
            }
        }
        else {
            if(Move == 1) {
                int BotBuy = GetRandomValue(1, 5);
                if(BotBuy == 1) {
                    if(Players[1].WarPoints >= Infantry_Cost) {
                        for(int i = 0; i < 10; ++i) {
                            if(Players[1].TroopBank[i].type == 'e') {
                                Players[1].TroopBank[i] = infantry;
                                Players[1].TroopBank[i].side = 'b';
                                Players[1].WarPoints -= Infantry_Cost;
                                MoveMade = 1;
                                break;
                            }
                        }
                    }
                }
                else if (BotBuy == 2) {
                    if(Players[1].WarPoints >= Medic_Cost) {
                        for(int i = 0; i < 10; ++i) {
                            if(Players[1].TroopBank[i].type == 'e') {
                                Players[1].TroopBank[i] = medic;
                                Players[1].TroopBank[i].side = 'b';
                                Players[1].WarPoints -= Medic_Cost;
                                MoveMade = 1;
                                break;
                            }
                        }
                    }
                }
                else if (BotBuy == 3) {
                    if(Players[1].WarPoints >= Artillery_Cost) {
                        for(int i = 0; i < 10; ++i) {
                            if(Players[1].TroopBank[i].type == 'e') {
                                Players[1].TroopBank[i] = artillery;
                                Players[1].TroopBank[i].side = 'b';
                                Players[1].WarPoints -= Artillery_Cost;
                                MoveMade = 1;
                                break;
                            }
                        }
                    }
                }
                else if (BotBuy == 4) {
                    if(Players[1].WarPoints >= Tank_Cost) {
                        for(int i = 0; i < 10; ++i) {
                            if(Players[1].TroopBank[i].type == 'e') {
                                Players[1].TroopBank[i] = tank;
                                Players[1].TroopBank[i].side = 'b';
                                Players[1].WarPoints -= Tank_Cost;
                                MoveMade = 1;
                                break;
                            }
                        }
                    }
                }
                else if (BotBuy == 5) {
                    if(Players[1].WarPoints >= Plane_Cost) {
                        for(int i = 0; i < 10; ++i) {
                            if(Players[1].TroopBank[i].type == 'e') {
                                Players[1].TroopBank[i] = plane;
                                Players[1].TroopBank[i].side = 'b';
                                Players[1].WarPoints -= Plane_Cost;
                                MoveMade = 1;
                                break;
                            }
                        }
                    }
                }
            }
            else if(Move == 2) {
                int BotTroopBankCount = 0;
                for(int i = 0; i < 10; ++i) {
                    if(Players[1].TroopBank[i].type != 'e') {
                        BotTroopBankCount++;
                    }
                }
                if(BotTroopBankCount) {
                    int BotTroopCount = 0;
                    bool BotCommanderHere = 0;
                    bool EnemyTroopIsHere = 0;
                    int BotBank = 0;
                    int BotTile = GetRandomValue(1, 47);
                    for(int i = 0; i < 10; ++i) {
                        if(Players[1].TroopBank[i].type != 'e') {
                            BotBank++;
                        }
                        if(Troops[BotTile - 1][i].side == 'b' && Troops[BotTile - 1][i].type == 'c') {
                            BotCommanderHere = 1;
                        }
                        if(Troops[BotTile - 1][i].side == 'b') {
                            BotTroopCount++;
                        }
                        if(Troops[BotTile - 1][i].side == 'r' && EnemyTroopIsHere == 0) {
                            EnemyTroopIsHere =  1;
                        }
                    }
                    if(BotTroopCount < 5 && ((EnemyTroopIsHere && BotCommanderHere) || (!EnemyTroopIsHere)) && BotBank) {
                        int BotChosen = GetRandomValue(1, BotBank);
                        for(int i = 0; i < 10; ++i) {
                            if(Troops[BotTile - 1][i].type == 'e') {
                                Troops[BotTile - 1][i] = Players[1].TroopBank[BotBank - 1];
                                Players[1].TroopBank[BotBank - 1] = empty_troop;
                                MoveMade = 1;
                            }
                        }
                    }
                }
            }
            else if(Move == 3) { // a bug causes bot troops not to move BotTile 4 (I don't even remember what were these bugs 7.09.2026)
                int BotFromTile = GetRandomValue(1, 47);
                int BotTroopCount = 0;
                vector<pair<troop, int>> BotTroops;
                for(int i = 0;i < 10; ++i) {
                    if(Troops[BotFromTile - 1][i].side == 'b' && GetRandomValue(1, 2) == 1) {
                        BotTroops.push_back({Troops[BotFromTile - 1][i], i});
                    }
                }
                if(BotTroops.size() > 0) {
                    int BotToTile = GetRandomValue(1, Tiles[BotFromTile - 1].size());
                    for(int i = 0; i < 10; ++i) {
                        if(Troops[Tiles[BotFromTile - 1][BotToTile - 1]][i].side == 'b') {
                            BotTroopCount++;
                        }
                    }
                    BotTroopCount += BotTroops.size();
                    if(BotTroopCount < 5) {
                        for(auto j : BotTroops) {
                            for(int i = 0; i < 10; ++i) {
                                if(Troops[BotToTile - 1][i].type == 'e') {
                                    Troops[BotToTile - 1][i] = Troops[BotFromTile - 1][j.second];
                                    Troops[BotFromTile - 1][j.second] = empty_troop;
                                }
                            }
                        }
                        MoveMade = 1;
                    }
                }
            }
            else if(Move == 4) { //EMERGENCY BUGFIX NEEDED (I don't even remember what were these bugs 7.09.2026)
                int BotTile = GetRandomValue(1, 47);
                vector<pair<troop,int>> BotTroops;
                for(int i = 0; i < 10; ++i) {
                    if(Troops[BotTile - 1][i].side == 'b' && Troops[BotTile - 1][i].type != 'c') {
                        BotTroops.push_back({Troops[BotTile - 1][i], i});
                    }
                }
                if(BotTroops.size() == 0) continue;
                int Slot = BotTroops[GetRandomValue(0, BotTroops.size() - 1)].second;
                        int First = 0;
                        int MaxHealth = 0;
                        switch(Troops[BotTile - 1][Slot].type) {
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
                                break;
                            default:
                                break;
                        }
                        Players[1].WarPoints += (First * 6 / 10) * (Troops[BotTile - 1][Slot].health / MaxHealth);
                        Troops[BotTile - 1][Slot] = empty_troop;
                        MoveMade = 1;
            }
            else if(Move == 5) {
                MoveMade = 1;
            }
        }
    }
    Round++;
    return;
}