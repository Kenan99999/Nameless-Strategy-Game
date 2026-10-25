#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOUSER
#include <raylib.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <memory>
#include <filesystem>
#include <set>
#include <enet/enet.h>
#include "globals.h"
#include "functions.h"
#include "packets.h"
struct tagMSG;
typedef struct tagMSG *LPMSG;

using namespace std;
using namespace filesystem;

bool DebugScreen() {
        if(IsKeyPressed(KEY_ESCAPE)) {
            return 1;
        }
        ClearBackground(WHITE);
        for (int i = 0; i < 5; ++i ) {
            DrawTexture(texture[i], 10, i * 200 + 10, WHITE);
            DrawText(TextFormat("Attack: %.1f", t[i].attack), 120, i * 200 + 10, 25, BLACK);
            DrawText(TextFormat("Defense: %.1f", t[i].defense), 120, i * 200 + 40, 25, BLACK);
            DrawText(TextFormat("Health: %.1f", t[i].health), 120, i * 200 + 70, 25, BLACK);
            DrawText(TextFormat("Air: %.1f", t[i].air_attack), 120, i * 200 + 100, 25, BLACK);
            DrawText(TextFormat("Heal: %.1f", t[i].heal), 120, i * 200 + 130, 25, BLACK);
            DrawText(TextFormat("Cost: %d", costs[i]), 120, i * 200 + 160, 25, BLACK);
            DrawText("DEBUG MODE", 800, 20, 50, BLACK);
        }
        if(IsKeyPressed(KEY_DOWN) && Selected < 5) {
            Selected++;
        }
        if(IsKeyPressed(KEY_UP) && Selected > 1) {
            Selected--;
        }
        DrawTexture(Tick, 500, (Selected - 1) * 200 + 10, WHITE);
        if((IsKeyPressed(KEY_ENTER) && Selected) || Entering) {
            Entering = 1;
            DrawRectangle(600, 100, 1020, 880, RAYWHITE);
            DrawText("Enter New Values", 610, 200, 30, BLACK);
            DrawText("Enter a new value and press space for every new value.\n(Repeat that for all 6 values)\nThen press 's' and you can see the values change.\nYou can then press esc and try it on a game.", 610, 700, 30, BLACK);
            DrawText(Values, 610, 420, 40, BLACK);
            TempKey = GetKeyPressed();
            if(TempKey == KEY_SPACE && index <= 31) {
                Values[index] = 95;
                index++;
            }
            else if(TempKey >= 48 && TempKey < 58 && index <= 31) {
                Values[index] = TempKey;
                index++;
            }
            else if(TempKey == KEY_BACKSPACE && index >= 1) {
                Values[index - 1] = '\0';
                index--;
            }
            if(IsKeyPressed(KEY_S)) {
                Values[index] = '\0';
                switch(Selected) {
                    case 1:
                        {
                        float Vals[6];
                        for(int i = 0; i < 6; ++i) {
                            Vals[i] = 0;
                        }
                        int indx = 0;
                        int count = 0;
                        int now = 0;
                        for(auto i : Values) {
                            if(i == '\0') {
                                break;
                            }
                            now++;
                            count++;
                            if(i == '_' && indx < 6) {
                                while(count > 1) {
                                    Vals[indx] += (float)(pow(10, (count - 2)) * ((int)Values[now - count] - 48));
                                    count--;
                                }
                                if(count == 1) {
                                    count = 0;
                                }
                                indx++;
                            }
                        }
                        infantry.attack = Vals[0];
                        infantry.defense = Vals[1];
                        infantry.health = Vals[2];
                        infantry.air_attack = Vals[3];
                        infantry.heal = Vals[4];
                        Infantry_Cost = Vals[5];
                        infantry.max_health = Vals[2];
                        costs[0] = Infantry_Cost;
                        Entering = 0;
                        t[0] = infantry;
                        for(int i = 0; i < 32; ++i) {
                            Values[i] = '\0';
                        }
                        index = 0;
                        break;
                        }

                    case 2:
                        {
                        float Vals[6];
                        for(int i = 0; i < 6; ++i) {
                            Vals[i] = 0;
                        }
                        int indx = 0;
                        int count = 0;
                        int now = 0;
                        for(auto i : Values) {
                            if(i == '\0') {
                                break;
                            }
                            now++;
                            count++;
                            if(i == '_' && indx < 6) {
                                while(count > 1) {
                                    Vals[indx] += (float)(pow(10, (count - 2)) * ((int)Values[now - count] - 48));
                                    count--;
                                }
                                if(count == 1) {
                                    count = 0;
                                }
                                indx++;
                            }
                        }
                        medic.attack = Vals[0];
                        medic.defense = Vals[1];
                        medic.health = Vals[2];
                        medic.air_attack = Vals[3];
                        medic.heal = Vals[4];
                        Medic_Cost = Vals[5];
                        medic.max_health = Vals[2];
                        costs[1] = Medic_Cost;
                        Entering = 0;
                        t[1] = medic;
                        for(int i = 0; i < 32; ++i) {
                            Values[i] = '\0';
                        }
                        index = 0;
                        break;
                        }

                    case 3:
                        {
                        float Vals[6];
                        for(int i = 0; i < 6; ++i) {
                            Vals[i] = 0;
                        }
                        int indx = 0;
                        int count = 0;
                        int now = 0;
                        for(auto i : Values) {
                            if(i == '\0') {
                                break;
                            }
                            now++;
                            count++;
                            if(i == '_' && indx < 6) {
                                while(count > 1) {
                                    Vals[indx] += (float)(pow(10, (count - 2)) * ((int)Values[now - count] - 48));
                                    count--;
                                }
                                if(count == 1) {
                                    count = 0;
                                }
                                indx++;
                            }
                        }
                        artillery.attack = Vals[0];
                        artillery.defense = Vals[1];
                        artillery.health = Vals[2];
                        artillery.air_attack = Vals[3];
                        artillery.heal = Vals[4];
                        Artillery_Cost = Vals[5];
                        artillery.max_health = Vals[2];
                        costs[2] = Artillery_Cost;
                        Entering = 0;
                        t[2] = artillery;
                        for(int i = 0; i < 32; ++i) {
                            Values[i] = '\0';
                        }
                        index = 0;
                        break;
                        }

                    case 4:
                        {
                        float Vals[6];
                        for(int i = 0; i < 6; ++i) {
                            Vals[i] = 0;
                        }
                        int indx = 0;
                        int count = 0;
                        int now = 0;
                        for(auto i : Values) {
                            if(i == '\0') {
                                break;
                            }
                            now++;
                            count++;
                            if(i == '_' && indx < 6) {
                                while(count > 1) {
                                    Vals[indx] += (float)(pow(10, (count - 2)) * ((int)Values[now - count] - 48));
                                    count--;
                                }
                                if(count == 1) {
                                    count = 0;
                                }
                                indx++;
                            }
                        }
                        tank.attack = Vals[0];
                        tank.defense = Vals[1];
                        tank.health = Vals[2];
                        tank.air_attack = Vals[3];
                        tank.heal = Vals[4];
                        Tank_Cost = Vals[5];
                        tank.max_health = Vals[2];
                        costs[3] = Tank_Cost;
                        Entering = 0;
                        t[3] = tank;
                        for(int i = 0; i < 32; ++i) {
                            Values[i] = '\0';
                        }
                        index = 0;
                        break;
                        }

                    case 5:
                        {
                        float Vals[6];
                        for(int i = 0; i < 6; ++i) {
                            Vals[i] = 0;
                        }
                        int indx = 0;
                        int count = 0;
                        int now = 0;
                        for(auto i : Values) {
                            if(i == '\0') {
                                break;
                            }
                            now++;
                            count++;
                            if(i == '_' && indx < 6) {
                                while(count > 1) {
                                    Vals[indx] += (float)(pow(10, (count - 2)) * ((int)Values[now - count] - 48));
                                    count--;
                                }
                                if(count == 1) {
                                    count = 0;
                                }
                                indx++;
                            }
                        }
                        plane.attack = Vals[0];
                        plane.defense = Vals[1];
                        plane.health = Vals[2];
                        plane.air_attack = Vals[3];
                        plane.heal = Vals[4];
                        Plane_Cost = Vals[5];
                        plane.max_health = Vals[2];
                        costs[4] = Plane_Cost;
                        Entering = 0;
                        t[4] = plane;
                        for(int i = 0; i < 32; ++i) {
                            Values[i] = '\0';
                        }
                        index = 0;
                        break;
                        }
                }
            }
        }
    return 0;
}