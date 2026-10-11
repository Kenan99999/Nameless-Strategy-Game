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
        }
    return 0;
}