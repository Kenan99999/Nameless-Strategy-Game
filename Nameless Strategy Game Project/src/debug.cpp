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
    for (int i = 0; i < 5; ++i ) {
        DrawText(TextFormat(""));
    }
    return;
}