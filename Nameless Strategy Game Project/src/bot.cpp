// Burayı en yakın zamanda düzelt

 /*void BotMove() {
    bool MoveMade = 0;
    while(!MoveMade) {
        int Move = GetRandomValue(1,5); // 1: Buy 2: Place 3: Move 4: Delete 5: SkipRound
        if(Round == 1) {
            int BotCommander = GetRandomValue(1, 4);
            if(Troops[BotCommander - 1][0].type == 'e') {
                Troops[BotCommander - 1][0] = commander;
                Troops[BotCommander - 1][0].side = 'b';
                MoveMade = 1;
            }
        }
        else {
            if(Move == 1) {
                int BotBuy = GetRandomValue(1, 4);
                if(BotBuy == 1) {
                    if(BlueWarPoints >= Infantry_Cost) {
                        for(int i = 0; i < 10; ++i) {
                            if(BlueTroopBank[i].type == 'e') {
                                BlueTroopBank[i] = infantry;
                                BlueTroopBank[i].side = 'b';
                                BlueWarPoints -= Infantry_Cost;
                                MoveMade = 1;
                                break;
                            }
                        }
                    }
                }
                else if (BotBuy == 2) {
                    if(BlueWarPoints >= Medic_Cost) {
                        for(int i = 0; i < 10; ++i) {
                            if(BlueTroopBank[i].type == 'e') {
                                BlueTroopBank[i] = medic;
                                BlueTroopBank[i].side = 'b';
                                BlueWarPoints -= Medic_Cost;
                                MoveMade = 1;
                                break;
                            }
                        }
                    }
                }
                else if (BotBuy == 3) {
                    if(BlueWarPoints >= Artillery_Cost) {
                        for(int i = 0; i < 10; ++i) {
                            if(BlueTroopBank[i].type == 'e') {
                                BlueTroopBank[i] = artillery;
                                BlueTroopBank[i].side = 'b';
                                BlueWarPoints -= Artillery_Cost;
                                MoveMade = 1;
                                break;
                            }
                        }
                    }
                }
                else if (BotBuy == 4) {
                    if(BlueWarPoints >= Tank_Cost) {
                        for(int i = 0; i < 10; ++i) {
                            if(BlueTroopBank[i].type == 'e') {
                                BlueTroopBank[i] = tank;
                                BlueTroopBank[i].side = 'b';
                                BlueWarPoints -= Tank_Cost;
                                MoveMade = 1;
                                break;
                            }
                        }
                    }
                }
                else if (BotBuy == 5) {
                    if(BlueWarPoints >= Plane_Cost) {
                        for(int i = 0; i < 10; ++i) {
                            if(BlueTroopBank[i].type == 'e') {
                                BlueTroopBank[i] = plane;
                                BlueTroopBank[i].side = 'b';
                                BlueWarPoints -= Plane_Cost;
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
                    if(BlueTroopBank[i].type != 'e') {
                        BotTroopBankCount++;
                    }
                }
                if(BotTroopBankCount) {
                    int BotTroopCount = 0;
                    bool BotCommanderHere = 0;
                    bool EnemyTroopIsHere = 0;
                    int BotBank = 0;
                    int BotTile = GetRandomValue(1,4);
                    for(int i = 0; i < 10; ++i) {
                        if(BlueTroopBank[i].type != 'e') {
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
                                Troops[BotTile - 1][i] = BlueTroopBank[BotBank - 1];
                                BlueTroopBank[BotBank - 1] = empty_troop;
                                MoveMade = 1;
                            }
                        }
                    }
                }
            }
            else if(Move == 3) { // a bug causes bot troops not to move tile 4
                int BotFromTile = GetRandomValue(1,4);
                int BotTroopCount = 0;
                vector<pair<troop, int>> BotTroops;
                for(int i = 0;i < 10; ++i) {
                    if(Troops[BotFromTile - 1][i].side == 'b') {
                        BotTroops.push_back({Troops[BotFromTile - 1][i], i});
                    }
                }
                if(BotTroops.size() > 0) {
                    int BotSelected = GetRandomValue(1, BotTroops.size());
                    int BotToTile = GetRandomValue(1, Tiles[BotFromTile - 1].size());
                    for(int i = 0; i < 10; ++i) {
                        if(Troops[Tiles[BotFromTile - 1][BotToTile - 1]][i].side == 'b') {
                            BotTroopCount++;
                        }
                    }
                    if(BotTroopCount < 5) {
                        for(int i = 0; i < 10; ++i) {
                            if(Troops[BotToTile - 1][i].type == 'e') {
                                Troops[BotToTile - 1][i] = Troops[BotFromTile - 1][BotTroops[BotSelected - 1].second];
                                Troops[BotFromTile - 1][BotTroops[BotSelected - 1].second] = empty_troop;
                                MoveMade = 1;
                                break;
                            }
                        }
                    }
                }
            }
            else if(Move == 4) { //EMERGENCY BUGFIX NEEDED
                int BotTile = GetRandomValue(1, 4);
                vector<pair<troop,int>> BotTroops;
                for(int i = 0; i < 10; ++i) {
                    if(Troops[BotTile - 1][i].side == 'b') {
                        BotTroops.push_back({Troops[BotTile - 1][i], i});
                    }
                }
                if(BotTroops.size() > 0 ) {
                    int BotSelected = GetRandomValue(1, BotTroops.size());
                    switch(Troops[BotTile - 1][BotTroops[BotSelected - 1].second].type) {
                        case 'i':
                            if(Troops[BotTile - 1][BotTroops[BotSelected - 1].second].health == 10) {
                                Troops[BotTile - 1][BotTroops[BotSelected - 1].second] = empty_troop;
                                BlueWarPoints += 3;
                                MoveMade = 1;
                            }
                            else if(Troops[BotTile - 1][BotTroops[BotSelected - 1].second].health >= 7) {
                                Troops[BotTile - 1][BotTroops[BotSelected - 1].second] = empty_troop;
                                BlueWarPoints += 2;
                                MoveMade = 1;
                            }
                            else if(Troops[BotTile - 1][BotTroops[BotSelected - 1].second].health >= 4) {
                                Troops[BotTile - 1][BotTroops[BotSelected - 1].second] = empty_troop;
                                BlueWarPoints += 1;
                                MoveMade = 1;
                            }
                            else {
                                Troops[BotTile - 1][BotTroops[BotSelected - 1].second] = empty_troop;
                                MoveMade = 1;
                            }
                            break;
                        case 'm':
                            if(Troops[BotTile - 1][BotTroops[BotSelected - 1].second].health == 5) {
                                Troops[BotTile - 1][BotTroops[BotSelected - 1].second] = empty_troop;
                                BlueWarPoints += 3;
                                MoveMade = 1;
                            }
                            else if(Troops[BotTile - 1][BotTroops[BotSelected - 1].second].health >= 3) {
                                Troops[BotTile - 1][BotTroops[BotSelected - 1].second] = empty_troop;
                                BlueWarPoints += 2;
                                MoveMade = 1;
                            }
                            else if(Troops[BotTile - 1][BotTroops[BotSelected - 1].second].health >= 2) {
                                Troops[BotTile - 1][BotTroops[BotSelected - 1].second] = empty_troop;
                                BlueWarPoints += 1;
                                MoveMade = 1;
                            }
                            else {
                                Troops[BotTile - 1][BotTroops[BotSelected - 1].second] = empty_troop;
                                MoveMade = 1;
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
            else if(Move == 5) {
                MoveMade = 1;
            }
        }
    }
    Round++;
    return;
}*/