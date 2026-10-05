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

void DebugScreen() {
    troop t[5];
    building b[5];
    t[0] = infantry;
    t[1] = medic;
    t[2] = artillery;
    t[3] = tank;
    t[4] = plane;
    b[0] = trench;
    b[1] = field_hospital;
    b[2] = anti_air;
    b[3] = repair_workshop;
    b[4] = army_house;
    for (int i = 0; i < 5; ++i ) {
        DrawText(TextFormat("%d", Infantry_Cost), 10, 10, 30, BLACK);
        DrawText("");
    }
    return;
}