#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOUSER
#include <raylib.h>
#include <bits/stdc++.h>
#include <enet/enet.h>
#include "globals.h"
#include "functions.h"
#include "packets.h"
struct tagMSG;
typedef struct tagMSG *LPMSG;

using namespace std;
using namespace filesystem;
void Combat(int PlayerCurrent) {
    int combatindex = 0;
    PACKET_COMBAT combat;
    for(int i = 0; i < 47; ++i) {
        char WhoWillUseTheBuilding1 = 'n';
        char WhoWillUseTheBuilding2 = 'n';
        int TotalTroops = 0;
        bool Situation = 0;
        char s;
        map<char, int> TakenDamages;
        TakenDamages['r'] = 0;
        TakenDamages['b'] = 0;
        TakenDamages['g'] = 0;
        TakenDamages['y'] = 0;
        TakenDamages['o'] = 0;
        TakenDamages['p'] = 0;
        map<char, int> AirTakenDamages;
        AirTakenDamages['r'] = 0;
        AirTakenDamages['b'] = 0;
        AirTakenDamages['g'] = 0;
        AirTakenDamages['y'] = 0;
        AirTakenDamages['o'] = 0;
        AirTakenDamages['p'] = 0;
        map<char, int> TroopCounts;
        TroopCounts['r'] = 0;
        TroopCounts['b'] = 0;
        TroopCounts['g'] = 0;
        TroopCounts['y'] = 0;
        TroopCounts['o'] = 0;
        TroopCounts['p'] = 0;
        float TeamCount = 0;
        troop TileOld[10];
        for(int j = 0; j < 10; ++j) {
            TileOld[j] = Troops[i][j];
            if(Troops[i][j].side != 'e' && Troops[i][j].type != 'c') {
                TroopCounts[Troops[i][j].side]++;
                TotalTroops++;
            }
        }
        for(auto j : TroopCounts) {
            if(j.second != 0) {
                TeamCount++;
            }
        }
        if(!TotalTroops || TeamCount < 2) {
            continue;
        }
        char Building1 = Buildings[i][0].WhoBuiltIt;
        char Building2 = Buildings[i][1].WhoBuiltIt;
        int maxx = 0;
        for(auto j : TroopCounts) {
            if(j.second > Situation) {
                Situation = j.first;
                s = j.first;
            }
            else if(j.second == Situation) {
                s = 'n';
            }
            if((j.second > maxx || (j.second >= maxx && j.first == Building1)) && Buildings[i][0].type != 'e') {
                WhoWillUseTheBuilding1 = j.first;
                maxx = j.first;
            }
            else if(j.second == maxx) {
                WhoWillUseTheBuilding1 = 'n';
            }
            if((j.second > maxx  || (j.second >= maxx && j.first == Building2)) && Buildings[i][1].type != 'e') {
                WhoWillUseTheBuilding2 = j.first;
                maxx = j.first;
            }
            else if(j.second == maxx) {
                WhoWillUseTheBuilding2 = 'n';
            }
        }
        for(int j = 0; j < PlayerCount; ++j) {
            if(Players[j].CommanderAvalible == 0) {
                continue;
            }
            float Attack = 0;
            float Defense = 0;
            float Air = 0;
            float Heal = 0;
            float Repair = 0;
            int TroopCount = 0;
            bool CommanderHere = 0;
            int r;
            int slot = 0;
            for(int k = 0; k < 10; ++k) {
                if(Troops[i][k].side == Players[j].color && Troops[i][k].type == 'c') {
                    CommanderHere = 1;
                    slot = k;
                }
                else if(Troops[i][k].side == Players[j].color) {
                    TroopCount++;
                    Defense += Troops[i][k].defense;
                    Heal += Troops[i][k].heal;
                }
            }
            for(int k = 0; k < 10; ++k) {
                if(Troops[i][k].side != Players[j].color) {
                    Attack += Troops[i][k].attack / (TeamCount - 1);
                    Air += Troops[i][k].air_attack / (TeamCount - 1);
                    if(CommanderHere && Attack && TroopCounts[Players[j].color] == 0) {
                        Players[j].CommanderAvalible = 0;
                        DeleteEliminatedTroops();
                        break;
                    }
                }
            }
            if(CommanderHere) {
                Defense *= 1.5;
            }
            if(Players[j].color == WhoWillUseTheBuilding1) {
                Attack *= Buildings[i][0].Attack;
                Air *= Buildings[i][0].AirAttack;
                Defense *= Buildings[i][0].Defense;
                Repair += Buildings[i][0].Repair;
                Heal += Buildings[i][0].Heal;
            }
            if(Players[j].color == WhoWillUseTheBuilding2) {
                Attack *= Buildings[i][1].Attack;
                Air *= Buildings[i][1].AirAttack;
                Defense *= Buildings[i][1].Defense;
                Repair += Buildings[i][1].Repair;
                Heal += Buildings[i][1].Heal;
            }
            if(Terrain[i] == "bridge" && s == Players[j].color) {
                Defense *= 1.5;
            }
            if(Terrain[i] == "forest" && s != Players[j].color) {
                Attack *= 0.8;
            }
            if(Terrain[i] == "city" && s == Players[j].color) {
                Defense *= 1.25;
            }
            if(Terrain[i] == "mountains") {
                if( s == Players[j].color ) Defense *= 1.5;
                else Attack *= 0.7;
            }
            if(Terrain[i] == "plains" && s == Players[j].color) {
                Defense *= 0.8;
            }
            if(Attack / 3 >= 1) Attack += rand() % int(Attack / 3);
            if(Defense / 3 >= 1) Defense += rand() % int(Defense / 3);
            if(Air / 5 >= 1) Air += rand() % int(Air / 5);
            if(Repair / 5 >= 1) Repair += rand() % int(Repair / 5);
            if(Heal / 3 >= 1) Heal += rand() % int(Heal / 3);
            float TakenDamage = Attack - Defense;
            TakenDamages[Players[j].color] = TakenDamage;
            AirTakenDamages[Players[j].color] = Air;
            for(int k = 0; k < 10; ++k) { //Healing
                if(Heal > 0 && Troops[i][k].side == Players[j].color && Troops[i][k].type != 'p') {
                    int AvalibleHeal = Troops[i][k].max_health - Troops[i][k].health;
                    if(AvalibleHeal > Heal) {
                        Troops[i][k].health += Heal;
                        Heal = 0;
                    }
                    else {
                        Troops[i][k].health += AvalibleHeal;
                        Heal -= AvalibleHeal;
                    }
                }
                else if(Repair > 0 && Troops[i][k].side == Players[j].color && Troops[i][k].type == 'p') {
                    int AvalibleHeal = Troops[i][k].max_health - Troops[i][k].health;
                    if(AvalibleHeal > Heal) {
                        Troops[i][k].health += Heal;
                        Heal = 0;
                    }
                    else {
                        Troops[i][k].health += AvalibleHeal;
                        Heal -= AvalibleHeal;
                    } 
                }
            }
        }
        for(int j = 0; j < PlayerCount; ++j) {
            float TakenDamage = TakenDamages[Players[j].color];
            float Air = AirTakenDamages[Players[j].color];
            bool CommanderHere = 0;
            if(TakenDamage <= 0 && Air <= 0) {
                continue;
            }
            int Slot = 0;
            for(int k = 0; k < 10; ++k) {
                if(Troops[i][k].side == Players[j].color && Troops[i][k].type == 'c') {
                    CommanderHere = 1;
                    Slot = k;
                }
                else if(Troops[i][k].side == Players[j].color && TakenDamage > Troops[i][k].health && Troops[i][k].type != 'p') {
                    TakenDamage -= Troops[i][k].health;
                    Troops[i][k] = empty_troop;
                }
                else if(Troops[i][k].side == Players[j].color && TakenDamage <= Troops[i][k].health && Troops[i][k].type != 'p') {
                    Troops[i][k].health -= TakenDamage;
                    TakenDamage = 0;
                }
                else if(Troops[i][k].side == Players[j].color && Air > Troops[i][k].health && Troops[i][k].type == 'p') {
                    Air -= Troops[i][k].health;
                    Troops[i][k] = empty_troop;
                }
                else if(Troops[i][k].side == Players[j].color && Air <= Troops[i][k].health && Troops[i][k].type == 'p') {
                    Troops[i][k].health -= Air;
                    Air = 0;
                }
            }
            if(CommanderHere && TakenDamage) {
                Players[j].CommanderAvalible = 0;
                DeleteEliminatedTroops();
            }
        }
        for(int j = 0; j < 10; ++j) {
            if(Troops[i][j].health != TileOld[j].health) {
                combat.NewTroopHealths[combatindex].first.first = i;
                combat.NewTroopHealths[combatindex].first.second = j;
                combat.NewTroopHealths[combatindex].second = Troops[i][j].health;
                combatindex++;
            }
        }
    }
    for(int j = 0; j < PlayerCount; ++j) {
        combat.CommanderAvalibility[j] = Players[j].CommanderAvalible;
    }
    combat.index = combatindex;
    if(PlayerCurrent == 2) {
        ENetPacket* combat_packet = enet_packet_create(&combat, sizeof(combat), ENET_PACKET_FLAG_RELIABLE);
        enet_host_broadcast(Server, 0, combat_packet);
    }
    CombatHappened = 1;
    return;
}