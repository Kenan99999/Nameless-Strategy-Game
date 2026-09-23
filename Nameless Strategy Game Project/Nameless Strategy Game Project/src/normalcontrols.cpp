#include "functions.h"
#include "globals.h"
#include <bits/stdc++.h>
#include <raylib.h>
using namespace std;

void ClearMouseCoords() {
    MouseX = 0;
    MouseY = 0;
    return;
}

void IncreaseWarPoints() {
    int r;
    for(int i = 0; i < PlayerCount; ++i) {
        r = rand();
        Players[i].WarPoints += (r % 2 + 2) + (Round / 100);
    }
    Increased = 1;
    return;
}

void GetMouseCoords() {
    MouseX = GetMouseX();
    MouseY = GetMouseY();
    return;
}

void Message(int PlayerID) {
    DrawRectangle(600, 250, 800, 500, WHITE);
    DrawTextureEx(Red_Icon, {610, 260}, 0.0f, 10.0f, WHITE);
    DrawTextureEx(Blue_Icon, {710, 260}, 0.0f, 10.0f, WHITE);
    if(PlayerCount > 2) DrawTextureEx(Green, {610, 360}, 0.0f, 10.0f, WHITE);
    if(PlayerCount > 3) DrawTextureEx(Yellow, {710, 360}, 0.0f, 10.0f, WHITE);
    if(PlayerCount > 4) DrawTextureEx(Orange, {610, 460}, 0.0f, 10.0f, WHITE);
    if(PlayerCount > 5) DrawTextureEx(Purple, {710, 460}, 0.0f, 10.0f, WHITE);
    if (LastMessage.second.first != 0) DrawText(TextFormat("Player %d says:\n %s", LastMessage.second.first, ChatPhrases[LastMessage.first].c_str()), 610, 570, 20, BLACK);
    if (LastMessage.second.second == PlayerID) DrawText(TextFormat("(To You)"), 610, 620, 20, BLACK);
    if(TargetID > 0 && ((MouseX - 510) / 100) + ((MouseY - 260) / 100) * 2 == TargetID) {
        TargetID = 0;
    }
    else if(MouseX >= 610 && MouseX <= 810 && MouseY >= 260 && MouseY <= 560) {
        TargetID = ((MouseX - 510) / 100) + ((MouseY - 260) / 100) * 2;
        if(TargetID > PlayerCount) {
            TargetID = 0;
        }
    }
    TempKey = GetKeyPressed();
    if(TempKey > KEY_ZERO && TempKey <= KEY_NINE) {
        Phrase = TempKey - 48;
    }
    for(int i = 0; i < ChatPhrases.size(); ++i) {
        DrawText(TextFormat("%d. %s", i + 1, ChatPhrases[i].c_str()), 900, 300 + 40 * i, 25, BLACK);
    }
    if(TargetID > 0) {
        DrawTexture(Tick, 610 + 100 * ((TargetID - 1) % 2), 260 + 100 * ((TargetID - 1) / 2), WHITE);
    }
    DrawText(TextFormat("Selected: %d", Phrase), 610, 670, 25, BLACK);
    return;
}
