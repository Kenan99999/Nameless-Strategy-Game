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


Music Intro;
enum PlayerType {
    PLAYER_NONE = 0,
    PLAYER_HOTSEAT = 1,
    PLAYER_CLIENT = 2,
    PLAYER_HOST = 3
};
int PlayerCurrent = PLAYER_NONE;
int PlayerID = 0;
int LocalPlay = 0;
bool ServerCreated = 0;
bool JoiningServer = 0;
bool InServer = 0;
bool LocalPlayersPushedBack = 0;
vector<char> HostIP;
// Functions
void DrawServerScreen() {
    if(PLAYER_NONE == PlayerCurrent) {
        DrawRectangle(200, 400, 600, 200, GRAY);
        DrawRectangle(1000, 400, 600, 200, GRAY);
        DrawText("Host", 210, 440, 50, BLACK);
        DrawText("Join", 1010, 440, 50, BLACK);
    }
    if(Server != nullptr && PlayerCurrent == PLAYER_HOST) {
        DrawRectangle(200, 400, 600, 200, GREEN);
        DrawText("Start the game", 210, 440, 50, BLACK);
        DrawText(TextFormat("PlayerCount: %d", LocalPlayerCount), 1100, 440, 50, BLACK);
    }
    else if(InServer && PlayerCurrent == PLAYER_CLIENT) {
        DrawText("Waiting for the host to start the game", 210, 440, 50, BLACK);
    }
    else if(JoiningServer == 0 && Peer != nullptr && PlayerCurrent == PLAYER_CLIENT) {
        DrawText("joining...", 600, 400, 50, BLACK);
    }
    else if(JoiningServer && PlayerCurrent == PLAYER_CLIENT) {
        DrawText("Enter Host IP and press enter", 600, 400, 50, BLACK);
        string IP_String(HostIP.begin(), HostIP.end());
        DrawText("IP: ", 600, 500, 50, BLACK);
        DrawText(IP_String.c_str(), 700, 500, 50, BLACK);
    }
}

void DrawSettingsScreen(Texture2D Restart_Icon, Texture2D Save_Icon, Texture2D Load_Icon) {
    ClearBackground(WHITE);
    DrawRectangle(800, 600, 320, 100, GRAY);
    DrawRectangle(800, 710, 320, 100, GRAY);
    DrawRectangle(800, 820, 320, 100, GRAY);
    DrawText("Close the game", 810, 610, 35, BLACK);
    DrawText("Show Bridge troops", 810, 720, 25, BLACK);
    DrawText(TextFormat("%.1f", ShowTroopsWhenZoomed), 1060, 830, 25, BLACK);
    DrawText("Show troops when\nzoomed more than", 810, 830, 25, BLACK);
    DrawText("Press Esc to return to the game", 600, 10, 60, BLACK);
    DrawTexture(Restart_Icon, 800, 490, WHITE);
    DrawTexture(Save_Icon, 910, 490, WHITE);
    DrawTexture(Load_Icon, 1020, 490, WHITE);
    if(ShowBridgeTroops) {
        DrawRectangle(1070, 760, 50, 50, GREEN);
    }
    else {
        DrawRectangle(1070, 760, 50, 50, RED);
    }
    if(ShowTroopsWhenZoomed > 1.0f) {
        DrawText("-", 1040, 900, 20, BLACK);
    }
    if(ShowTroopsWhenZoomed < 2.9f) {
        DrawText("+", 1080, 900, 20, BLACK);
    }
}
void DrawHowToPlayScreen(Texture2D Infantry_Icon, Texture2D Medic_Icon, Texture2D Commander_Icon, Texture2D Artillery_Icon, Texture2D Tank_Icon, Texture2D Plane_Icon) {
    DrawText(TextFormat("Page %d/2", Page + 1), 920, 1050, 25, BLACK);
    // Comments were an old easter egg in version Pre-alpha 0.8.1
    if(IsKeyPressed(KEY_LEFT) && Page > 0) {
        Page--;
    }
    if(IsKeyPressed(KEY_RIGHT) && Page < 1) {
        Page++;
    }
    /*if(IsKeyPressed(KEY_K)) {
        Page = -1;
    }*/
    if(Page == 1) {
        DrawText("<-", 10, 1050, 25, BLACK);
        DrawTexture(Commander_Icon, 10, 10, WHITE);
        DrawText("This is commander and every player only have 1 of these.\nThe main goal of the game is to kill the enemy commander.\nCommander stats-> Health:1, Attack:0, Defense:0, Heal:0, Air:0\n(Commander gives a 1,5x attack boost to friendly troops)", 112, 10, 25, BLACK);
        DrawTexture(Infantry_Icon, 10, 150, WHITE);
        DrawText("The cheapest attack option.\nInfantry stats-> Health:10, Attack:2, Defense:1, Heal:0, Air:0", 112, 150, 25, BLACK);
        DrawTexture(Medic_Icon, 10, 290, WHITE);
        DrawText("A troop that heals your army.\nMedic stats-> Health:5, Attack:0, Defense:1, Heal:2, Air:0", 112, 290, 25, BLACK);
        DrawTexture(Artillery_Icon, 10, 430, WHITE);
        DrawText("A strong attack troop.\nArtillery stats-> Health:15, Attack:5, Defense:0, Heal:0, Air:3", 112, 430, 25, BLACK);
        DrawTexture(Tank_Icon, 10, 570, WHITE);
        DrawText("A strong troop for both attack and defense.\nTank stats-> Health:30, Attack:10, Defense:5, Heal:0, Air:1", 112, 570, 25, BLACK);
        DrawTexture(Plane_Icon, 10, 710, WHITE);
        DrawText("Only air attack can damage it and medic can't heal it.\nPlane stats-> Health:20, Attack:5, Defense:2, Heal:0, Air:7", 112, 710, 25, BLACK);

        DrawTexture(Trench_Icon, 960, 10, WHITE);
        DrawText("Trench increases defense by 1.3x", 1062, 10, 25, BLACK);
        DrawTexture(FieldHospital_Icon, 960, 150, WHITE);
        DrawText("Field hospital heals troops 5 health every round", 1062, 150, 25, BLACK);
        DrawTexture(AntiAir_Icon, 960, 290, WHITE);
        DrawText("Anti-Air increases air attack by 1.3x", 1062, 290, 25, BLACK);
        DrawTexture(RepairWorkshop_Icon, 960, 430, WHITE);
        DrawText("Repair workshop heals planes 5 health every round", 1062, 430, 25, BLACK);
        DrawTexture(ArmyHouse_Icon, 960, 570, WHITE);
        DrawText("Army House increases attack by 1.3x", 1062, 570, 25, BLACK);
    }
    else if(Page == 0) {
        DrawText("->", 1890, 1050, 25, BLACK);
        /*DrawText("<-", 10, 380, 18, BLACK);*/
        DrawText("How rounds work: Every round you can only make 1 action. Actions include buying, skipping, moving, placing and deleting\n(Bought troops will be sent into the troop bank waiting for placement)", 10, 10, 25, BLACK);
        DrawText("How warpoints work: Warpoints are the main currency to buy troops. It will increase 2 or 3 randomly every 5 * (Player count - 1) rounds\nand will get a +1 increase every 100 rounds.\n(For instance it will increase 4 or 5 randomly at round 205)", 10, 200, 25, BLACK);
        DrawText("How combat works: Combat happens at the start of every round Taken damage will be calculated by the formula enemyattack - yourdefense\nTaken damage will lower you troops health while heal increases it. Air troops like plane will only be damaged with air attack\n(Combat includes a little bit of randomness for fun)", 10, 400, 25, BLACK);
        DrawText("How tiles work: Each tile has a different terrain every terrain gives certain bonuses and debuffs\nForest: Attack 0.8x, Plains: Defense 0.8x, Mountains: Attack 0.75x, Defense 1.5x, City: Defense 1.25x, Bridge: Defense 1.5x, Hills: No effect", 10, 600, 25, BLACK);
    }
    /*else {
        DrawText("->", 630, 380, 18, BLACK);
        DrawText("48 46 57\n45 65 100 ? ? 100 98 117 ? 108 100 105 ? 115", 10 , 180, 20, BLACK);
        DrawText("?543??5?4535?2432?567?87646????654?243\n????5435?4351?213214325?6546??4??????", 10 , 10, 20, BLACK);
        DrawText("?543??5?45??5435?4351?213214335?243\n??25?6546??4??2432?567?87646????654?????", 10 , 300, 20, BLACK);
    }*/
}

void GameSave() {
    DrawRectangle(700, 400, 600, 200, GRAY);
    DrawText("File name:\n(Max 10 characters)", 700, 200, 70, BLACK);
    DrawText("Press enter to save\nClick anywhere to cancel", 700, 620, 40, BLACK);
    DrawText(SaveName, 710, 420, 70, BLACK);
    TempKey = GetKeyPressed();
    if(TempKey >= 65 && TempKey <= 90 && index <= 9) {
        if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) SaveName[index] = TempKey;
        else SaveName[index] = TempKey + 32;
        index++;
    }
    else if(TempKey == 45 && index <= 9) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            SaveName[index] = 95;
            index++;
        }
    }
    else if(TempKey >= 48 && TempKey < 58 && index <= 9) {
        SaveName[index] = TempKey;
        index++;
    }
    else if(TempKey == KEY_BACKSPACE && index >= 1) {
        SaveName[index - 1] = '\0';
        index--;
    }
    if(IsKeyPressed(KEY_ENTER) && index >= 1) {
        if(!exists("saves")) {
            create_directory("saves");
        }
        if(GameSaves.size() >= 10) {
            cout << "You can't create more than 10 saves!" << endl;
            SaveScreen = 0;
            index = 0;
            return;
        }
        string file_addres = "saves/" + (string)SaveName + ".save";
        ofstream File(file_addres);

        if(File.is_open()) {
            File << PlayerCount << endl;
            for(int i = 0; i < PlayerCount; ++i) {
                File << Players[i].color << endl;
                File << Players[i].CommanderAvalible << endl;
                for(int j = 0; j < 10; ++j) {
                    File << Players[i].TroopBank[j].type << endl;
                    File << Players[i].TroopBank[j].side << endl;
                    File << Players[i].TroopBank[j].health << endl;
                    File << Players[i].TroopBank[j].attack << endl;
                    File << Players[i].TroopBank[j].defense << endl;
                    File << Players[i].TroopBank[j].heal << endl;
                    File << Players[i].TroopBank[j].max_health << endl;
                }
                File << Players[i].WarPoints << endl;
            }
            File << Round << endl;
            File << RedWarPoints << endl;
            File << BlueWarPoints << endl;
            File << CombatHappened << endl;
            File << PlayWithABot << endl;
            File << Increased << endl;
            for(int i = 0; i < 47; ++i) {
                for(int j = 0; j < 2; ++j) {
                    File << Buildings[i][j].type << endl;
                    File << Buildings[i][j].WhoBuiltIt << endl;
                    File << Buildings[i][j].health << endl;
                    File << Buildings[i][j].Attack << endl;
                    File << Buildings[i][j].Defense << endl;
                    File << Buildings[i][j].AirAttack << endl;
                    File << Buildings[i][j].Heal << endl;
                    File << Buildings[i][j].Repair << endl;
                    File << Buildings[i][j].max_health << endl;
                    File << Buildings[i][j].cost << endl;
                }
            }
        }

        SaveScreen = 0;
        index = 0;
    }
    if(MouseClicked) {
        SaveScreen = 0;
        index = 0;
    }
    return;
}
void ReArrangeTroops() {
    for(int i = 0; i < 47; ++i) {
        for(int j = 0; j < 10; ++j) {
            if(Troops[i][j].type == 'e') {
                for(int k = j; k < 10; ++k) {
                    if(Troops[i][k].type != 'e') {
                        Troops[i][j] = Troops[i][k];
                        Troops[i][k] = empty_troop;
                        break;
                    }
                }
            }
        }
    }
    for(int k = 0; k < PlayerCount; ++k) {
        for(int i = 0;i < 10; ++i) {
            if(Players[k].TroopBank[i].type == 'e') {
                for(int j = i; j < 10; ++j) {
                    if(Players[k].TroopBank[j].type != 'e') {
                        Players[k].TroopBank[i] = Players[k].TroopBank[j];
                        Players[k].TroopBank[j] = empty_troop;
                        break;
                    }
                }
            }
        }
    }
}
void restart() {
    GameStarted = 0;
    Action = 0;
    RedWarPoints = 10;
    BlueWarPoints = 10;
    PixelX = 0;
    PixelY = 0;
    MouseX = 0;
    MouseY = 0;
    TileSelected = 0;
    FromTileSelected = 0;
    ToTileSelected = 0;
    Round = 0;
    GhostRounds = 0;
    MouseClicked = 0;
    Checkbox = 0;
    EmptyCounter = 0;
    IncreaseControl = 0;
    Increased = 0;
    BoughtTroop = 0;
    PressedKeyI = 0;
    PressedKeyM = 0;
    PressedKeyC = 0;
    PressedKeyP = 0;
    TroopChosen = 0;
    IsTileOkay = 1;
    ItIsAnEmptySlot = 0;
    IsCommanderHere = 0;
    CreditScreen = 0;
    MouseCleared = 0;
    CombatHappened = 0;
    LastClickedX = 0;
    LastClickedY = 0;
    LastRound = 0;
    Action = 0;
    SaveScreen = 0;
    LoadScreen = 0;
    SettingsScreen = 0;
    SelectedSave = 0;
    PlayWithABot = 0;
    Page = 0;
    index = 0;
}
/*void Combat() {
    for(int i = 0; i < 47; ++i) {
        char WhoWillUseTheBuilding1 = 'n';
        char WhoWillUseTheBuilding2 = 'n';
        int TotalTroops = 0;
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
        for(int j = 0; j < 10; ++j) {
            if(Troops[i][j].side != 'e' && Troops[i][j].type != 'c') {
                TroopCounts[Troops[i][j].side]++;
                TotalTroops++;
            }
        }
        if(!TotalTroops) {
            continue;
        }
        char Building1 = Buildings[i][0].WhoBuiltIt;
        char Building2 = Buildings[i][1].WhoBuiltIt;
        int maxx = 0;
        for(auto j : TroopCounts) {
            if((j.second > maxx || (j.second >= maxx && j.first == Building1)) && Buildings[i][0].type != 'e') {
                WhoWillUseTheBuilding1 = j.first;
            }
            else if(j.second == maxx) {
                WhoWillUseTheBuilding1 = 'n';
            }
            if((j.second > maxx  || (j.second >= maxx && j.first == Building2)) && Buildings[i][1].type != 'e') {
                WhoWillUseTheBuilding2 = j.first;
            }
            else if(j.second == maxx) {
                WhoWillUseTheBuilding1 = 'n';
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
                    Attack += Troops[i][k].attack / (TotalTroops - TroopCounts[Troops[i][k].side]);
                    Air += Troops[i][k].air_attack / (TotalTroops - TroopCounts[Troops[i][k].side]);
                    if(CommanderHere && (Attack || Air) && TroopCounts[Players[j].color] == 0) {
                        Players[j].CommanderAvalible = 0;
                        Troops[i][slot] = empty_troop;
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
            if(Terrain[i] == "bridge") {
                Defense *= 1.5;
            }
            if(Terrain[i] == "forest") {
                Attack *= 0.8;
            }
            if(Terrain[i] == "city") {
                Defense *= 1.25;
            }
            if(Terrain[i] == "mountains") {
                Defense *= 1.5;
                Attack *= 0.7;
            }
            if(Terrain[i] == "plains") {
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
            if(CommanderHere && (TakenDamage || Air)) {
                Players[j].CommanderAvalible = 0;
                Troops[i][Slot] = empty_troop;
            }
        }
    }
    CombatHappened = 1;
    return;
}*/
void DrawCreditsandChangelogScreen() {
    DrawText("Changelog:", 10, 10, 40, BLACK);
    DrawText("Credits:", 960, 10, 40, BLACK);
    DrawText("0.10.1:\n- Player count added\n- Major and minor bugfixes\nPS: Bot is not working and will crash your\ngame if you try to play but will\nbe readded soon\n0.10.1.1:\n- Added a setting\n- Intro sound effect\n- bugfixes", 10, 150, 30, BLACK);
    DrawText("Main Developer:\nKenan Mert Pamuk\nTextures:\nÖmer Kaymak\n\nMade with:\nC++/Raylib", 960, 150, 30, BLACK);
    DrawText("Version: Pre-alpha 0.10.1.1", 10, 1040, 30, BLACK);
}
Texture2D DrawTroopHealth(int Health, char type, Texture2D Low_health, Texture2D Medium_health, Texture2D High_health, Texture2D Full_health) {
    switch(type) {
        case 'i':
            if(Health == Infantry_Full) {
                return Full_health;
            }
            else if(Health >= Infantry_Full * 7 / 10) {
                return High_health;
            }
            else if(Health >= Infantry_Full * 4 / 10) {
                return Medium_health;
            }
            else return Low_health;
            break;
        case 'm':
            if(Health == Medic_Full) {
                return Full_health;
            }
            else if(Health >= Medic_Full * 7 / 10) {
                return High_health;
            }
            else if(Health >= Medic_Full * 4 / 10) {
                return Medium_health;
            }
            else return Low_health;
            break;
        case 'a':
            if(Health == Artillery_Full) {
                return Full_health;
            }
            else if(Health >= Artillery_Full * 7 / 10) {
                return High_health;
            }
            else if(Health >= Artillery_Full * 4 / 10) {
                return Medium_health;
            }
            else return Low_health;
            break;
        case 't':
            if(Health == Tank_Full) {
                return Full_health;
            }
            else if(Health >= Tank_Full * 7 / 10) {
                return High_health;
            }
            else if(Health >= Tank_Full * 4 / 10) {
                return Medium_health;
            }
            else return Low_health;
            break;
        case 'p':
            if(Health == Plane_Full) {
                return Full_health;
            }
            else if(Health >= Plane_Full * 7 / 10) {
                return High_health;
            }
            else if(Health >= Plane_Full * 4 / 10) {
                return Medium_health;
            }
            else return Low_health;
            break;
        case 'c':
            return Full_health;
            break;
        default:
            break;
    }
    return Low_health;
}
Texture2D DrawTroopIcon(char type, Texture2D Infantry_Icon, Texture2D Medic_Icon, Texture2D Commander_Icon, Texture2D Empty_Icon, Texture2D Artillery_Icon, Texture2D Tank_Icon, Texture2D Plane_Icon) {
    switch(type) {
        case 'i':
            return Infantry_Icon;
        case 'm':
            return Medic_Icon;
        case 'c':
            return Commander_Icon;
        case 'e':
            return Empty_Icon;
        case 'a':
            return Artillery_Icon;
        case 't':
            return Tank_Icon;
        case 'p':
            return Plane_Icon;
        default:
            break;
    }
    return Empty_Icon;
}
Texture2D DrawSide(char Side, Texture2D Red_Icon, Texture2D Blue_Icon) {
    switch(Side) {
        case 'r':
            return Red_Icon;
        case 'b':
            return Blue_Icon;
        case 'g':
            return Green;
        case 'y':
            return Yellow;
        case 'o':
            return Orange;
        case 'p':
            return Purple;
        default:
            break;
    }
    cout << "ERROR" << endl;
    return Red_Icon;
}
Texture2D DrawBuildingIcon(char type, Texture2D Empty_Icon) {
    switch(type) {
        case 't':
            return Trench_Icon;
        case 'f':
            return FieldHospital_Icon;
        case 'a':
            return AntiAir_Icon;
        case 'r':
            return RepairWorkshop_Icon;
        case 'h':
            return ArmyHouse_Icon;
        case 'e':
            return Empty_Icon;
        default:
            break;
    }
    return Empty_Icon;
}
void DrawBuildingBuyScreen(Texture2D Empty_Icon, Texture2D WarPoint) {
    DrawTexture(Trench_Icon, 10, 10, WHITE);
    DrawTexture(FieldHospital_Icon, 10, 120, WHITE);
    DrawTexture(AntiAir_Icon, 10, 230, WHITE);
    DrawTexture(RepairWorkshop_Icon, 10, 340, WHITE);
    DrawTexture(ArmyHouse_Icon, 10, 450, WHITE);
    DrawTextureEx(WarPoint, {180, 10}, 0.0f, 0.5f, WHITE);
    DrawTextureEx(WarPoint, {180, 120}, 0.0f, 0.5f, WHITE);
    DrawTextureEx(WarPoint, {180, 230}, 0.0f, 0.5f, WHITE);
    DrawTextureEx(WarPoint, {180, 340}, 0.0f, 0.5f, WHITE);
    DrawTextureEx(WarPoint, {180, 450}, 0.0f, 0.5f, WHITE);
    DrawText(TextFormat("%d", trench.cost), 120, 10, 50, BLACK);
    DrawText(TextFormat("%d", field_hospital.cost), 120, 120, 50, BLACK);
    DrawText(TextFormat("%d", anti_air.cost), 120, 230, 50, BLACK);
    DrawText(TextFormat("%d", repair_workshop.cost), 120, 340, 50, BLACK);
    DrawText(TextFormat("%d", army_house.cost), 120, 450, 50, BLACK);
    DrawText("T", 15, 15, 25, BLACK);
    DrawText("F", 15, 125, 25, BLACK);
    DrawText("A", 15, 235, 25, BLACK);
    DrawText("R", 15, 345, 25, BLACK);
    DrawText("H", 15, 455, 25, BLACK);
    return;
}

void DrawTitleScreen(Texture2D Logo) {
    DrawRectangle(200, 400, 600, 200, GRAY);
    DrawRectangle(1000, 400, 600, 200, GRAY);
    DrawText("Play with friends", 250, 450, 50, BLACK);
    DrawText(TextFormat("Player count: %d", PlayerCount), 250, 550, 35, BLACK);
    if(PlayerCount < 6) DrawText("+", 750, 550, 35, BLACK);
    if(PlayerCount > 2) DrawText("-", 700, 550, 35, BLACK);
    DrawText("Play with a bot\n(Disabled for now)", 1050, 450, 50, BLACK);
    DrawText("Version: Pre-alpha 0.10.1.1", 10, 1040, 30, BLACK);
    DrawTextureEx(Logo, {10, 10}, 0.0f, 2.0f, WHITE);
    DrawText("NAMELESS GAME", 800, 10, 65, BLACK);
    DrawRectangle(1600, 800, 300, 120, GRAY);
    DrawText("Changelog and\nCredits", 1610, 810, 35, BLACK);
    DrawRectangle(1600, 940, 300, 120, GRAY);
    DrawText("How to play", 1610, 950, 35, BLACK);
    DrawRectangle(200, 620, 600, 200, GRAY);
    DrawText("Close the game", 210, 640, 50, BLACK);
    DrawRectangle(1000, 620, 600, 200, GRAY);
    DrawText("Play local", 1010, 640, 50, BLACK);
}
void DrawLogoScreen(Texture2D Logo) {
    DrawTextureEx(Logo, {460, 10}, 0.0f, 20.0f, WHITE);
}
void DrawTick(Texture2D Tick, int x, int y) {
    DrawTexture(Tick, x, y, WHITE);
    return;
}

void DrawRound(int Map_width, int Map_height) {
    DrawText(TextFormat("Round %d", Round + 1 - GhostRounds), MapBorderX + Map_width - 170, MapBorderY, 30, BLACK);
    return;
}

void TroopBuying(Texture2D Tick) {
    TempKey = GetKeyPressed();
    if(TempKey == KEY_I) {
        BoughtTroop = 1;
    }
    else if(TempKey == KEY_M) {
        BoughtTroop = 2;
    }
    else if(TempKey == KEY_A) {
        BoughtTroop = 3;
    }
    else if(TempKey == KEY_T) {
        BoughtTroop = 4;
    }
    else if(TempKey == KEY_P) {
        BoughtTroop = 5;
    }
    if(BoughtTroop) DrawTick(Tick, 10, (BoughtTroop - 1) * 110 + 10);
    return;
}
void BuyBuilding(Texture2D Tick) {
    TempKey = GetKeyPressed();
    if(TempKey == KEY_T) {
        BoughtBuilding = 1;
        BuiltBuilding = trench;
    }
    else if(TempKey == KEY_F) {
        BoughtBuilding = 2;
        BuiltBuilding = field_hospital;
    }
    else if(TempKey == KEY_A) {
        BoughtBuilding = 3;
        BuiltBuilding = anti_air;
    }
    else if(TempKey == KEY_R) {
        BoughtBuilding = 4;
        BuiltBuilding = repair_workshop;
    }
    else if(TempKey == KEY_H) {
        BoughtBuilding = 5;
        BuiltBuilding = army_house;
    }
    if(BoughtBuilding) DrawTick(Tick, 10, (BoughtBuilding- 1) * 100 + 10);
    return;
}
void DrawTroopBuyScreen(Texture2D Infantry_Icon, Texture2D Medic_Icon, Texture2D WarPoint, Texture2D Artillery_Icon, Texture2D Tank_Icon, Texture2D Plane_Icon) {
    DrawTexture(Infantry_Icon, 10, 10, WHITE);
    DrawTexture(Medic_Icon, 10, 120, WHITE);
    DrawTexture(Artillery_Icon, 10, 230, WHITE);
    DrawTexture(Tank_Icon, 10, 340, WHITE);
    DrawTexture(Plane_Icon, 10, 450, WHITE);
    DrawTextureEx(WarPoint, {180, 10}, 0.0f, 0.5f, WHITE);
    DrawTextureEx(WarPoint, {180, 120}, 0.0f, 0.5f, WHITE);
    DrawTextureEx(WarPoint, {180, 230}, 0.0f, 0.5f, WHITE);
    DrawTextureEx(WarPoint, {180, 340}, 0.0f, 0.5f, WHITE);
    DrawTextureEx(WarPoint, {180, 450}, 0.0f, 0.5f, WHITE);
    DrawText(TextFormat("%d", Infantry_Cost), 120, 10, 50, BLACK);
    DrawText(TextFormat("%d", Medic_Cost), 120, 120, 50, BLACK);
    DrawText(TextFormat("%d", Artillery_Cost), 120, 230, 50, BLACK);
    DrawText(TextFormat("%d", Tank_Cost), 120, 340, 50, BLACK);
    DrawText(TextFormat("%d", Plane_Cost), 120, 450, 50, BLACK);
    DrawText("I", 15, 15, 25, BLACK);
    DrawText("M", 15, 125, 25, BLACK);
    DrawText("A", 15, 235, 25, BLACK);
    DrawText("T", 15, 345, 25, BLACK);
    DrawText("P", 15, 455, 25, BLACK);
    DrawText("To skip don't buy\nanything and confirm.", 10, 550, 35, BLACK);
    return;
}
int ControlCheckboxes() { // Yes or No
    if(IsKeyPressed(KEY_Q)) {
        return 1;
    }
    else if (IsKeyPressed(KEY_E)){
        return 2;
    }
    else {
        return 0;
    }
}
void DrawCheckboxes() {
    DrawRectangle(10, 990, 80, 80, GREEN);
    DrawRectangle(100, 990, 80, 80, RED);
    DrawText("Q", 15, 993, 80, BLACK);
    DrawText("E", 105, 993, 80, BLACK);
    return;
}

void DrawTurn(Texture2D WarPoint) {
    if(Round % PlayerCount == 0) {
        DrawText("Red", 230, 970, 40, RED);
        DrawText(TextFormat("%d", Players[Round % PlayerCount].WarPoints), 230, 1015, 40, RED);
        DrawTextureEx(WarPoint, {335, 1015}, 0.0f, 0.6f, WHITE);
    }
    else if(Round % PlayerCount == 1){
        DrawText("Blue", 230, 970, 40, BLUE);
        DrawText(TextFormat("%d", Players[Round % PlayerCount].WarPoints), 230, 1015, 40, BLUE);
        DrawTextureEx(WarPoint, {335, 1015}, 0.0f, 0.6f, WHITE);
    }
    else if(Round % PlayerCount == 2){
        DrawText("GREEN", 230, 970, 40, GREEN);
        DrawText(TextFormat("%d", Players[Round % PlayerCount].WarPoints), 230, 1015, 40, GREEN);
        DrawTextureEx(WarPoint, {335, 1015}, 0.0f, 0.6f, WHITE);
    }
    else if(Round % PlayerCount == 3){
        DrawText("YELLOW", 230, 970, 40, YELLOW);
        DrawText(TextFormat("%d", Players[Round % PlayerCount].WarPoints), 230, 1015, 40, YELLOW);
        DrawTextureEx(WarPoint, {335, 1015}, 0.0f, 0.6f, WHITE);
    }
    else if(Round % PlayerCount == 4){
        DrawText("ORANGE", 230, 970, 40, ORANGE);
        DrawText(TextFormat("%d", Players[Round % PlayerCount].WarPoints), 230, 1015, 40, ORANGE);
        DrawTextureEx(WarPoint, {335, 1015}, 0.0f, 0.6f, WHITE);
    }
    else if(Round % PlayerCount == 5){
        DrawText("PURPLE", 230, 970, 40, PURPLE);
        DrawText(TextFormat("%d", Players[Round % PlayerCount].WarPoints), 230, 1015, 40, PURPLE);
        DrawTextureEx(WarPoint, {335, 1015}, 0.0f, 0.6f, WHITE);
    }
    return;
}
void ChangeTileSelected() {
    if(MouseX >= MapBorderX && MouseX <= MapBorderX + Map_png.width && MouseY >= MapBorderY && MouseY <= MapBorderY + Map_png.height && MouseClicked) {
        PixelX = MouseX - MapBorderX;
        PixelY = MouseY - MapBorderY;

        MouseColor = GetImageColor(Map_png, PixelX, PixelY);
        if(MouseColor.r > 0) {
            TileSelected = MouseColor.r / 10;
        }
        else if(MouseColor.b > 0) {
            //TileSelected = MouseColor.b / 10 + 38;
            TileSelected = 0;
        }
        else if(MouseColor.g > 0)  {
            TileSelected = MouseColor.g / 10 + 25;
        }
    }
    else if(MouseClicked) {
        TileSelected = 0;
    }
    return;
}
void DrawTileSelected() {
    if(TileSelected == 0) DrawText("Select \na tile", 10, 10, 50, BLACK);
    else { 
        if(TileSelected <= 47) DrawText(TextFormat("Tile %d", TileSelected), 10, 10, 50, BLACK);
        else DrawText("water", 10, 10, 50, BLACK);
        DrawText(Terrain[TileSelected - 1].c_str(), 10, 70, 50, BLACK);
    }
}
void CommanderPlacement() {
    DrawTileSelected();
    if(MouseClicked) ChangeTileSelected();
    DrawText("Select a tile to\nplace your commander\nchoose wisely", 10, 800, 26, BLACK);
    if(TileSelected != 0) {
        if(MouseClicked) GetMouseCoords();
        DrawCheckboxes();
        Checkbox = ControlCheckboxes();
        if(Checkbox == 1) {
            if(PlayerCurrent == PLAYER_HOTSEAT) {
                if(IsCommanderPlacementOkay(TileSelected, (Round % PlayerCount) + 1)) {
                    Action = 0;
                }
                TileSelected = 0;
            }
            else if(PlayerCurrent == PLAYER_HOST) {
                if(IsCommanderPlacementOkay(TileSelected, PlayerID)) {
                    PACKET_COMMANDER_PLACEMENT commander_placed;
                    commander_placed.PlayerID = PlayerID;
                    commander_placed.Tile = TileSelected;
                    
                    ENetPacket* commander_placed_packet = enet_packet_create(&commander_placed, sizeof(commander_placed), ENET_PACKET_FLAG_RELIABLE);
                    enet_host_broadcast(Server, 0, commander_placed_packet);
                    Action = 0;
                    TileSelected = 0;
                }
            }
            else if(PlayerCurrent == PLAYER_CLIENT) {
                PACKET_COMMANDER_PLACEMENT commander_placed;
                commander_placed.PlayerID = PlayerID;
                commander_placed.Tile = TileSelected;

                ENetPacket* commander_placed_packet = enet_packet_create(&commander_placed, sizeof(commander_placed), ENET_PACKET_FLAG_RELIABLE);
                enet_peer_send(Peer, 0, commander_placed_packet);
            }
        }
        else if(Checkbox == 2) {
            TileSelected = 0;
        }
        Checkbox = 0;
    }
}

void PlaceScreen(Texture2D Infantry_Icon, Texture2D Medic_Icon, Texture2D Commander_Icon, Texture2D Empty_Icon, Texture2D Tick, Image Map, int Map_width, int Map_height, Texture2D Low_health, Texture2D Medium_health, Texture2D High_health, Texture2D Full_health, Texture2D Artillery_Icon, Texture2D Tank_Icon, Texture2D Plane_Icon) {

        if(!TroopChosen) {
            DrawText("Select a troop from\nyour troop bank to place", 10, 600, 29, BLACK);
            for(int i = 0; i < 10; ++i) {
                TempDraw = DrawTroopIcon(Players[Round % PlayerCount].TroopBank[i].type, Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Artillery_Icon, Tank_Icon, Plane_Icon);
                DrawTexture(TempDraw, (i % 2) * 110 + 10, (i / 2) * 110 + 10, WHITE);
                DrawText(TextFormat("%d", i), (i % 2) * 110 + 90, (i / 2) * 110 + 14, 25, BLACK);
            }
            TempKey = GetKeyPressed() - 47;
            if(TempKey >= 1 && TempKey <= 10) {
                Key = TempKey;
            }
            if(Key > 0) {
                DrawTexture(Tick, ((Key - 1) % 2) * 110 + 10, ((Key - 1) / 2) * 110 + 10, WHITE);
                SelectedTroop = Players[Round % PlayerCount].TroopBank[Key - 1];
            }
        }
        else {
            ChangeTileSelected();
            DrawTileSelected();
            if(Checkbox == 1 && TileSelected != 0) {
                if(PlayerCurrent != PLAYER_CLIENT) {
                    bool okay = IsPlacementOkay(TileSelected, Round % PlayerCount);
                    if(PlayerCurrent == PLAYER_HOST && okay) {
                        PACKET_PLACE_TROOP placement;
                        placement.Tile = TileSelected;
                        placement.ID = 1;
                        placement.Slot = EmptyCounter - 1;
                        placement.Troop = SelectedTroop;
                        ENetPacket* placement_packet = enet_packet_create(&placement, sizeof(placement), ENET_PACKET_FLAG_RELIABLE);
                        enet_host_broadcast(Server, 0, placement_packet);
                    }
                    if(okay) {
                        Key = 0;
                        TileSelected = 0;
                    }
                }
                else if(PlayerCurrent == PLAYER_CLIENT) {
                    PACKET_PLACE_TROOP placement;
                    placement.Tile = TileSelected;
                    placement.ID = PlayerID;
                    placement.Slot = 0;
                    placement.Troop = SelectedTroop;
                    ENetPacket* placement_packet = enet_packet_create(&placement, sizeof(placement), ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(Peer, 0, placement_packet);
                }
            }
        }
        DrawCheckboxes();
        Checkbox = ControlCheckboxes();
        if(Checkbox == 2) {
            Action = 0;
            PressedKeyC = 0;
            PressedKeyP = 0;
            PressedKeyM = 0;
            Checkbox = 0;
            TempKey = 0;
            TroopChosen = 0;
            TileSelected = 0;
            Key = 0;
        }
        else if(Checkbox == 1 && (SelectedTroop.type == 'e' || SelectedTroop.type == 'n')) {
            cout << "Please choose an appropriate troop" << endl;
        }
        else if(Checkbox == 1) {
            TroopChosen = 1;
        }
}
void MoveScreen(Texture2D Infantry_Icon, Texture2D Medic_Icon, Texture2D Commander_Icon, Texture2D Empty_Icon, Texture2D Tick, Image Map, int Map_width, int Map_height, Texture2D Red_Icon, Texture2D Blue_Icon, Texture2D Low_health, Texture2D Medium_health, Texture2D High_health, Texture2D Full_health, Texture2D Artillery_Icon, Texture2D Tank_Icon, Texture2D Plane_Icon) {
    if(!FromTileSelected) {
        DrawText("Select a tile to move a troop\nfrom that tile", 10, 700, 25, BLACK);
        ChangeTileSelected();
        DrawTileSelected();
        DrawCheckboxes();
        Checkbox = ControlCheckboxes();
    }
    if(Checkbox == 1) {
        FromTileSelected = TileSelected;
        Checkbox = 0;
    }
    else if(Checkbox == 2) {
        FromTileSelected = 0;
        TileSelected = 0;
        ItIsAnEmptySlot = 0;
        TroopChosen = 0;
        Action = 0;
        MovingTroop.type = 'n';
        Key = 0;
        PressedKeyM = 0;
        PressedKeyC = 0;
        PressedKeyP = 0;
        Checkbox = 0;
        return;
    }
    if(FromTileSelected != 0) {
        if(!TroopChosen) {
            for(int i = 0; i < 10; ++i) {
                TempDraw = DrawTroopIcon(Troops[FromTileSelected - 1][i].type, Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Artillery_Icon, Tank_Icon, Plane_Icon);
                DrawTexture(TempDraw, ((i % 2) * 110 + 10), (i / 2) * 110 + 10, WHITE);
                if(Troops[FromTileSelected - 1][i].type != 'e') { 
                    RedBlue = DrawSide(Troops[FromTileSelected - 1][i].side, Red_Icon, Blue_Icon);
                    DrawTextureEx(RedBlue, {(float)(i % 2) * 110 + 10, (float)(i / 2) * 110 + 10}, 0.0f, 2.0f, WHITE);
                    Health = DrawTroopHealth(Troops[FromTileSelected - 1][i].health, Troops[FromTileSelected - 1][i].type, Low_health, Medium_health, High_health, Full_health);
                    DrawTexture(Health, ((i % 2) * 110 + 14), (i / 2) * 110 + 92, WHITE);
                }
                if(MovingTroops.find(i) != MovingTroops.end()) {
                    DrawTick(Tick,((i % 2) * 110 + 10), (i / 2) * 110 + 10);
                }
                DrawText(TextFormat("%d", i), ((i % 2) * 110 + 90), (i / 2) * 110 + 14, 25, BLACK);
                DrawCheckboxes();
                Checkbox = ControlCheckboxes();
                if(Checkbox == 1 && MovingTroops.size() > 0) {
                    TroopChosen = 1;
                    Checkbox = 0;
                    TileSelected = 0;
                    break;
                }
                else if(Checkbox == 2) {
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
                    return;
                }
                TempKey = GetKeyPressed() - 47;
                if(TempKey >= 1 && TempKey <= 10) {
                    Key = TempKey;
                }
                if(Key > 0 && Key < 11) {
                    if(MovingTroops[Key - 1].type != (Troops[FromTileSelected - 1][Key - 1]).type && MovingTroops.size() < 5) MovingTroops[Key - 1] = (Troops[FromTileSelected - 1][Key - 1]);
                    else if(MovingTroops.size() >= 5) cout << "you can't move more than 5 troops!" << endl;
                    else MovingTroops.erase(Key - 1);
                    Key = 0;
                }
            }
            for(int i = 0; i < 2; ++i) {
                TempDraw = DrawBuildingIcon(Buildings[FromTileSelected - 1][i].type, Empty_Icon);
                DrawTexture(TempDraw, 10 + i * 110, 600, WHITE);
            }
        }
        else {
            for(auto i : MovingTroops) {
                if(i.second.side != Players[Round % PlayerCount].color) {
                    cout << "You can't move (an) enemy troop(s)" << endl;
                    TroopChosen = 0;
                }
                else if(i.second.side == 'e') {
                    cout << "You chose (an) empty slot(s)" << endl;
                    TroopChosen = 0;
                    break;
                }
            }
            if(TroopChosen) {
                DrawTileSelected();
                ChangeTileSelected();
                DrawCheckboxes();
                Checkbox = ControlCheckboxes();
                if(Checkbox == 1) {
                    ToTileSelected = TileSelected;
                    if(PlayerCurrent == PLAYER_HOTSEAT) {
                        IsMovingOkay(FromTileSelected, ToTileSelected, Round % PlayerCount);
                    }
                    if(PlayerCurrent == PLAYER_HOST) {
                        if(IsMovingOkay(FromTileSelected, ToTileSelected, PlayerID - 1)) {
                            PACKET_MOVE_TROOP moving;
                            moving.FromTile = FromTileSelected;
                            moving.ToTile = ToTileSelected;
                            moving.ID = PlayerID;
                            int index = 0; 
                            for(int i = 0; i < 5; ++i) {
                                moving.Moving[i].second.type = 'e';
                            }
                            for(auto i : MovingTroopsCopy) {
                                moving.Moving[index] = {i.first, i.second};
                                index++;
                            }
                            ENetPacket* move_packet = enet_packet_create(&moving, sizeof(moving), ENET_PACKET_FLAG_RELIABLE);
                            enet_host_broadcast(Server, 0, move_packet);
                        }
                    }
                    if(PlayerCurrent == PLAYER_CLIENT) {
                        PACKET_MOVE_TROOP moving;
                        moving.FromTile = FromTileSelected;
                        moving.ToTile = ToTileSelected;
                        moving.ID = PlayerID;
                        int index = 0;
                        for(int i = 0; i < 5; ++i) {
                            moving.Moving[i].second.type = 'e';
                        }
                        for(auto i : MovingTroops) {
                            moving.Moving[index] = {i.first, i.second};
                            index++;
                        }
                        ENetPacket* move_packet = enet_packet_create(&moving, sizeof(moving), ENET_PACKET_FLAG_RELIABLE);
                        enet_peer_send(Peer, 0, move_packet);   
                    }
                    MovingTroops.clear();
                    MovingTroopsCopy.clear();
                }
                else if(Checkbox == 2) {
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
                    return;
                }
            }
        }
    }
}
void DrawMoveandPlaceTroopsScreen() {
    if(!PressedKeyC && !PressedKeyP && IsKeyPressed(KEY_M)) {
        PressedKeyM = 1;
    }
    else if(!PressedKeyC && !PressedKeyM && IsKeyPressed(KEY_P)) {
        PressedKeyP = 1;
    }
    else if(!PressedKeyM && !PressedKeyP && IsKeyPressed(KEY_C)) {
        PressedKeyC = 1;
    }
    else if(!PressedKeyP && !PressedKeyC && !PressedKeyM) {
        DrawText("Press M to move a troop\nPress P to place a troop\nPress C to cancel", 10, 10, 30, BLACK);
    }
    if(PressedKeyP) {
        PlaceScreen(Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Tick, Map_png, Map_png.width, Map_png.height, Low_health, Medium_health, High_health, Full_health, Artillery_Icon, Tank_Icon, Plane_Icon);
        return;
    }
    else if(PressedKeyC) {
        Action = 0;
        PressedKeyM = 0;
        PressedKeyC = 0;
        PressedKeyP = 0;
        return;
    }
    else if(PressedKeyM) {
        MoveScreen(Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Tick, Map_png, Map_png.width, Map_png.height, Red_Icon, Blue_Icon, Low_health, Medium_health, High_health, Full_health, Artillery_Icon, Tank_Icon, Plane_Icon);
    }
}
void DrawDeleteTroopsScreen(Image Map, Texture2D Infantry_Icon, Texture2D Medic_Icon, Texture2D WarPoint, Texture2D Tick, Texture2D Commander_Icon, Texture2D Empty_Icon, Texture2D Red_Icon, Texture2D Blue_Icon, Texture2D Low_health, Texture2D Medium_health, Texture2D High_health, Texture2D Full_health, Texture2D Artillery_Icon, Texture2D Tank_Icon, Texture2D Plane_Icon) {
    if(TileSelected == 0) {
        DrawTileSelected();
        ChangeTileSelected();
    }
    else {
        if(!TroopChosen) {
            for(int i = 0; i < 10; ++i) {
                TempDraw = DrawTroopIcon(Troops[TileSelected - 1][i].type, Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Artillery_Icon, Tank_Icon, Plane_Icon);
                DrawTexture(TempDraw, (i % 2) * 110 + 10, (i / 2) * 110 + 10, WHITE);
                if(Troops[TileSelected - 1][i].type != 'e') { 
                    RedBlue = DrawSide(Troops[TileSelected - 1][i].side, Red_Icon, Blue_Icon);
                    DrawTextureEx(RedBlue, {(float)(i % 2) * 110 + 10, (float)(i / 2) * 110 + 10}, 0.0f, 2.0f, WHITE);
                    Health = DrawTroopHealth(Troops[TileSelected - 1][i].health, Troops[TileSelected - 1][i].type, Low_health, Medium_health, High_health, Full_health);
                    DrawTexture(Health, (i % 2) * 110 + 14, (i / 2) * 110 + 92, WHITE);
                }
                DrawText(TextFormat("%d", i), (i % 2) * 110 + 90, (i / 2) * 110 + 14, 25, BLACK);
                TempKey = GetKeyPressed() - 47;
                if(TempKey >= 1 && TempKey <= 10) {
                    Key = TempKey;
                }
            }
            if(Key > 0 && Key < 11) {
                DrawTexture(Tick, ((Key - 1) % 2) * 110 + 10, ((Key - 1) / 2) * 110 + 10, WHITE);
            }
            DrawCheckboxes();
            Checkbox = ControlCheckboxes();
            if(Checkbox == 1 && Key) {
                TroopChosen = 1;
            }
            else if(Checkbox == 2) {
                TroopChosen = 0;
                ItIsAnEmptySlot = 0;
                Action = 0;
                Checkbox = 0;
                TileSelected = 0;
                Key = 0;
                return;
            }
        }
        else {
            if(PlayerCurrent == PLAYER_HOTSEAT) {
                if(DeleteTheTroop(Round % PlayerCount, TileSelected - 1, Key - 1)) {
                    PointDifferance = 0;
                    TileSelected = 0;
                    Key = 0;
                }
            }
            else if(PlayerCurrent == PLAYER_HOST) {
                if(DeleteTheTroop(PlayerID - 1, TileSelected - 1, Key - 1)) {
                    PACKET_DELETE_TROOP delete_troop;
                    delete_troop.ID = PlayerID;
                    delete_troop.NewWarPoints = PointDifferance;
                    delete_troop.Tile = TileSelected;
                    delete_troop.Slot = Key;
                    ENetPacket* delete_packet = enet_packet_create(&delete_troop, sizeof(delete_troop), ENET_PACKET_FLAG_RELIABLE);
                    enet_host_broadcast(Server, 0, delete_packet);
                    PointDifferance = 0;
                    TileSelected = 0;
                    Key = 0;
                }
            }
            else if(PlayerCurrent == PLAYER_CLIENT) {
                PACKET_DELETE_TROOP delete_troop;
                delete_troop.ID = PlayerID;
                delete_troop.NewWarPoints = 0;
                delete_troop.Tile = TileSelected;
                delete_troop.Slot = Key - 1;
                ENetPacket* delete_packet = enet_packet_create(&delete_troop, sizeof(delete_troop), ENET_PACKET_FLAG_RELIABLE);
                enet_peer_send(Peer, 0, delete_packet);
                TileSelected = 0;
                Key = 0;
            }
        }
    }
    return;
}
void DrawBuildScreen(Image Map, Texture2D Empty_Icon, Texture2D WarPoint, Texture2D Tick) {
    if(!TileSelected) {
        ChangeTileSelected();
        DrawTileSelected();
        DrawText("Choose a tile to build", 10, 600, 30, BLACK);
    }
    else {
        DrawBuildingBuyScreen(Empty_Icon, WarPoint);
        BuyBuilding(Tick);
        DrawCheckboxes();
        Checkbox = ControlCheckboxes();
        int Slot = 0;
        if(Checkbox == 1) {
            IsTileOkay = 0;
            for(int i = 0; i < 2; ++i) {
                if(Buildings[TileSelected - 1][i].type == 'e') {
                    IsTileOkay = 1;
                    Slot = i;
                    break;
                }
            }
            if(PlayerCurrent == PLAYER_HOTSEAT) {
                IsBuildOkay(Round % PlayerCount, Slot);
            }
            if(PlayerCurrent == PLAYER_HOST) {
                if(IsBuildOkay(PlayerID - 1, Slot)) {
                    PACKET_BUILD build;
                    build.Tile = TileSelected;
                    build.Who = PlayerID;
                    ENetPacket* build_packet = enet_packet_create(&build, sizeof(build), ENET_PACKET_FLAG_RELIABLE);
                    enet_host_broadcast(Server, 0, build_packet);
                }
            }
            if(PlayerCurrent == PLAYER_CLIENT) {
                PACKET_BUILD build;
                build.Tile = TileSelected;
                build.Who = PlayerID;
                ENetPacket* build_packet = enet_packet_create(&build, sizeof(build), ENET_PACKET_FLAG_RELIABLE);
                enet_peer_send(Peer, 0, build_packet);
            }
        }
        else if(Checkbox == 2) {
            BoughtBuilding = 0;
            TileSelected = 0;
            Action = 0;
            IsTileOkay = 1;
        }
    }
}
void DrawActions() {
    if(Round < PlayerCount) {
        CommanderPlacement();
    }
    else if(Action == 0) { // Red's Turn and actions
        DrawText("Choose an action", 10, 10, 30, BLACK);
        DrawRectangle(10, 10 + 40, 185, 80, GRAY);
        DrawRectangle(10, 100 + 40, 185, 80, GRAY);
        DrawRectangle(205, 10 + 40, 185, 80, GRAY);
        DrawRectangle(205, 100 + 40, 185, 80, GRAY);
        DrawText("Buy Troop\n/Skip Round", 15, 10 + 40, 25, BLACK);
        DrawText("Move/Place\nTroop", 15, 105 + 40, 25, BLACK);
        DrawText("Delete\nTroop", 210, 15 + 40, 25, BLACK);
        DrawText("Build\na building", 210, 105 + 40, 25, BLACK);
        DrawText(SelectedTip.c_str(), 10, 200 + 40, 30, BLACK);
        if(MouseClicked) {
            GetMouseCoords();
            if(MouseX >= 10 && MouseX <= 195 && MouseY >= 10 + 40 && MouseY <= 90 + 40) {
                Action = 1;
                SelectedTip = GameplayTips[GetRandomValue(0,1)];
            }
            else if(MouseX >= 205 && MouseX <= 390 && MouseY >= 10 + 40 && MouseY <= 90 + 40) {
                Action = 3;
                SelectedTip = GameplayTips[GetRandomValue(0,1)];
            }
            else if(MouseX >= 10 && MouseX <= 195 && MouseY >= 100 + 40 && MouseY <= 180 + 40) {
                Action = 2;
                SelectedTip = GameplayTips[GetRandomValue(0,1)];
            }
            else if(MouseX >= 205 && MouseX <= 390 && MouseY >= 100 + 40 && MouseY <= 180 + 40) {
                Action = 4;
                SelectedTip = GameplayTips[GetRandomValue(0,1)];
            }
        }

    }
    else if(Action == 1) {
        DrawTroopBuyScreen(Infantry_Icon, Medic_Icon, WarPoint, Artillery_Icon, Tank_Icon, Plane_Icon);
        DrawCheckboxes();
        Checkbox = ControlCheckboxes();
        if(Checkbox == 2) {
            Action = 0;
            Checkbox = 0;
            BoughtTroop = 0;
            PressedKeyI = 0;
            PressedKeyM = 0;
        }
        else if(Checkbox == 1) {
            if(BoughtTroop != 0) {
                if (PlayerCurrent == PLAYER_HOTSEAT || PlayerCurrent == PLAYER_HOST)  {
                    AddBoughtTroopToTheTroopBank(BoughtTroop, Round % PlayerCount);
                    if(PlayerCurrent == PLAYER_HOST) {
                        PACKET_ROUND increase;
                        ENetPacket* increase_packet = enet_packet_create(&increase, sizeof(increase), ENET_PACKET_FLAG_RELIABLE);
                        enet_host_broadcast(Server, 0, increase_packet);
                    }
                }
                else if(PlayerCurrent == PLAYER_CLIENT) {
                    PACKET_BUY_TROOP buy_troop;
                    buy_troop.PlayerID = PlayerID;
                    buy_troop.BoughtTroop = BoughtTroop;
                    ENetPacket* buy_troop_packet = enet_packet_create(&buy_troop, sizeof(buy_troop), ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(Peer, 0, buy_troop_packet);
                }
                Action = 0;
                Checkbox = 0;
                BoughtTroop = 0;
                PressedKeyI = 0;
                PressedKeyM = 0;
            }
            else {
                if(PlayerCurrent == PLAYER_HOTSEAT) {
                    Round++;
                }
                else if(PlayerCurrent == PLAYER_HOST) {
                    Round++;
                    PACKET_ROUND increase;
                    ENetPacket* increase_packet = enet_packet_create(&increase, sizeof(increase), ENET_PACKET_FLAG_RELIABLE);
                    enet_host_broadcast(Server, 0, increase_packet);
                }
                else if(PlayerCurrent == PLAYER_CLIENT) {
                    PACKET_ROUND increase;
                    ENetPacket* increase_packet = enet_packet_create(&increase, sizeof(increase), ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(Peer, 0, increase_packet);
                }
                Action = 0;
                Checkbox = 0;
                BoughtTroop = 0;
                PressedKeyI = 0;
                PressedKeyM = 0;
                cout << "Skipped the round" << endl;
            }
        }
        TroopBuying(Tick);
    }
    else if(Action == 2) {
        DrawMoveandPlaceTroopsScreen();
    }
    else if(Action == 3) {
        DrawDeleteTroopsScreen(Map_png, Infantry_Icon, Medic_Icon, WarPoint, Tick, Commander_Icon, Empty_Icon, Red_Icon, Blue_Icon, Low_health, Medium_health, High_health, Full_health, Artillery_Icon, Tank_Icon, Plane_Icon);
    }
    else if(Action == 4) {
        DrawBuildScreen(Map_png, Empty_Icon, WarPoint, Tick);
    }
}
void GameLoadScreen(Texture2D Tick, Texture2D TrashBin) {
    for(int i = 0; i < 10; ++i) {
        DrawRectangle((i / 5) * 650 + 100, (i % 5) * 150 + 20, 600, 100, GRAY);
        DrawText(TextFormat("%d", i), (i / 5) * 650 + 102, (i % 5) * 150 + 22, 30, BLACK);
        if(GameSaves.size() > i) {
            string ShowingName = path(GameSaves[i]).stem().string();
            DrawText(ShowingName.c_str(), (i / 5) * 650 + 105, (i % 5) * 150 + 60, 45, BLACK);
        }
    }
    TempKey = GetKeyPressed() + 1;
    if(TempKey >= 49 && TempKey <= 58) SelectedSave = TempKey - 48;
    if(SelectedSave > 0) DrawTick(Tick, ((SelectedSave - 1) / 5) * 650 + 600, ((SelectedSave - 1) % 5) * 150 + 20);
    DrawCheckboxes();
    Checkbox = ControlCheckboxes();
    DrawTexture(TrashBin, 1810, 970, WHITE);
    if(Checkbox == 2) {
        TempKey = 0;
        SelectedSave = 0;
        LoadScreen = 0;
        Checkbox = 0;
        return;
    }
    else if(Checkbox == 1) {
        if(SelectedSave - 1 < GameSaves.size()) {
            string LoadingFile = "saves/" + GameSaves[SelectedSave - 1];
            ifstream File(LoadingFile);

            if(exists(LoadingFile)) {
                if(File.is_open()) {
                    File >> PlayerCount;
                    while(Players.size() > 0) {
                        Players.pop_back();
                    }
                    if(PlayerCount >= 1) {
                        Players.push_back(red);
                        Players.push_back(blue);
                    }
                    if(PlayerCount >= 3) {
                        Players.push_back(green);
                    }
                    if(PlayerCount >= 4) {
                        Players.push_back(yellow);
                    }
                    if(PlayerCount >= 5) {
                        Players.push_back(orange);
                    }
                    if(PlayerCount >= 6) {
                        Players.push_back(purple);
                    }
                    ClearTroops();
                    for(int i = 0; i < PlayerCount; ++i) {
                        File >> Players[i].color;
                        File >> Players[i].CommanderAvalible;
                        for(int j = 0; j < 10; ++j) {
                            File >> Players[i].TroopBank[j].type;
                            File >> Players[i].TroopBank[j].side;
                            File >> Players[i].TroopBank[j].health;
                            File >> Players[i].TroopBank[j].attack;
                            File >> Players[i].TroopBank[j].defense;
                            File >> Players[i].TroopBank[j].heal;
                            File >> Players[i].TroopBank[j].max_health;
                        }
                        File >> Players[i].WarPoints;
                    }
                    File >> Round;
                    File >> RedWarPoints;
                    File >> BlueWarPoints;
                    for(int i = 0; i < 47; ++i) {
                        for(int j = 0; j < 10; ++j) {
                            File >> Troops[i][j].type;
                            File >> Troops[i][j].side;
                            File >> Troops[i][j].health;
                            File >> Troops[i][j].attack;
                            File >> Troops[i][j].defense;
                            File >> Troops[i][j].heal;
                            File >> Troops[i][j].max_health;
                        }
                    }
                    File >> CombatHappened;
                    File >> PlayWithABot;
                    File >> Increased;
                    for(int i = 0; i < 4; ++i) {
                        for(int j = 0; j < 2; ++j) {
                            File >> Buildings[i][j].type;
                            File >> Buildings[i][j].WhoBuiltIt;
                            File >> Buildings[i][j].health;
                            File >> Buildings[i][j].Attack;
                            File >> Buildings[i][j].Defense;
                            File >> Buildings[i][j].AirAttack;
                            File >> Buildings[i][j].Heal;
                            File >> Buildings[i][j].Repair;
                            File >> Buildings[i][j].max_health;
                            File >> Buildings[i][j].cost;
                        }
                    }
                }
                TempKey = 0;
                SelectedSave = 0;
                LoadScreen = 0;
                Checkbox = 0;
                return;
            }
        }
    }
    if(MouseClicked && MouseX >= 1810 && MouseX <= 1910 && MouseY >= 970 && MouseY <= 1070 && SelectedSave > 0 && SelectedSave - 1 < GameSaves.size()) {
        cout << SelectedSave << endl;
        string DeletingFilePath = "saves/" + GameSaves[SelectedSave - 1];
        if(exists(DeletingFilePath)) {
            remove(DeletingFilePath);
        }
        GameSaves.erase(GameSaves.begin() + (SelectedSave - 1));
        SelectedSave = 0;
        TempKey = 0;
        return;
    } 
    return;
}

void DrawTroops(Texture2D Infantry_Icon, Texture2D Medic_Icon, Texture2D Commander_Icon, Texture2D Empty_Icon, Texture2D Red_Icon, Texture2D Blue_Icon, Texture2D Low_health, Texture2D Medium_health, Texture2D High_health, Texture2D Full_health, Texture2D Artillery_Icon, Texture2D Tank_Icon, Texture2D Plane_Icon) {
    if(GameCamera.zoom >= ShowTroopsWhenZoomed) {
        for(int j = 0; j < Centers.size(); ++j) {
            if((j >= 41 && ShowBridgeTroops) || j < 41) {
                for(int i = 0; i < 10; ++i) {
                    TempDraw = DrawTroopIcon(Troops[j][i].type, Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Artillery_Icon, Tank_Icon, Plane_Icon);
                    Health = DrawTroopHealth(Troops[j][i].health, Troops[j][i].type, Low_health, Medium_health, High_health, Full_health);

                    DrawTextureEx(TempDraw, {(float)(i % 5) * 24 + Centers[j].first, (float)(i / 5) * 24 + Centers[j].second}, 0, 0.2, WHITE);
                    if(Troops[j][i].type != 'e') {
                        RedBlue = DrawSide(Troops[j][i].side, Red_Icon, Blue_Icon);
                        DrawTextureEx(Health, {(float)(i % 5) * 24 + Centers[j].first + 1, (float)(i / 5) * 24 + Centers[j].second + 18}, 0, 0.2, WHITE);
                        DrawTextureEx(RedBlue, {(float)(i % 5) * 24 + Centers[j].first, (float)(i / 5) * 24 + Centers[j].second}, 0, 0.4f, WHITE);
                    }
                }
                for(int i = 0; i < 2; ++i) {
                    TempDraw = DrawBuildingIcon(Buildings[j][i].type, Empty_Icon);
                    DrawTextureEx(TempDraw, {(float)Centers[j].first + i * 24, (float)48 + Centers[j].second}, 0, 0.2, WHITE);
                }
            }
        }
    }
}


int main() {
    if(TileSelector) {
        TileCenterSelector();
    }
    CreateTerrains();
    CreateMapBonds();
    InitWindow(screenWidth, screenHeight, "Nameless Strategy Game");
    LoadGameTextures();
    SetWindowState(FLAG_WINDOW_ALWAYS_RUN);
    //ToggleBorderlessWindowed();

    GameplayTips[0] = "Gameplay\ntip:\nWar Points\nwill increase\nrandomly\nevery\n5 rounds";
    GameplayTips[1] = "Gameplay\ntip:\nMedic can't\nheal a\nplane";
    SelectedTip = GameplayTips[GetRandomValue(0,1)];
    SetTargetFPS(60);
    float TimePlayed = 0;
    InitAudioDevice();
    Intro = LoadMusicStream("sounds/intro.mp3");
    PlayMusicStream(Intro);
    SetMusicVolume(Intro, 1.0f);
    SetMusicPan(Intro, 0.0f);
    restart:
    bool TroopsCleared = 0;
    GameCamera.target = {MapBorderX, MapBorderY};
    GameCamera.offset = {MapBorderX, MapBorderY};
    GameCamera.rotation = 0.0f;
    GameCamera.zoom = 1.0f;
    restart();
    while(Players.size() > 0) {
        Players.pop_back();
    }
    Saves();
    SelectedTroop.type = 'n';
    MovingTroop.type = 'n';
    int GameShouldEnd = 0;
    int GameDraw = 0;
    if(enet_initialize() != 0) {
        cout << "control your internet" << endl;
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);
    ENetAddress Host_Address;
    Host_Address.port = 2222;
    Host_Address.host = ENET_HOST_ANY;
    ENetAddress Client_Address;
    Client_Address.port = 2222;
    while(!CloseTheWindow) { // Main Game Loop
        if(IsKeyPressed(KEY_F4) && IsKeyDown(KEY_LEFT_ALT)) {
            CloseTheWindow = 1;
            continue;
        }
        ENetEvent event;
        if(LocalPlay && Server != nullptr) { //server
            while(enet_host_service(Server, &event, 0) > 0) {
                switch(event.type) {
                    case ENET_EVENT_TYPE_CONNECT:
                    {
                        if(GameStarted || LocalPlayerCount >= 6) {
                            cout << "Game already started or maximum capacity has been reached" << endl;
                            enet_peer_disconnect_now(event.peer, 0);
                            LocalPlay = 0;
                            PlayerCurrent = PLAYER_NONE;
                            HostIP.clear();
                            continue;
                        }
                        else {
                            LocalPlayerCount++;
                            event.peer->data = (void*)(uintptr_t)LocalPlayerCount;
                            cout << "player " << LocalPlayerCount  << " joined" << endl;
                            PACKET_PLAYER_JOIN Join;
                            Join.ID = LocalPlayerCount;
                            Join.CurrentPlayerCount = LocalPlayerCount;

                            ENetPacket* join_packet = enet_packet_create(&Join, sizeof(Join), ENET_PACKET_FLAG_RELIABLE);
                            enet_peer_send(event.peer, 0, join_packet);
                        }
                        break;
                    }
                    case ENET_EVENT_TYPE_DISCONNECT:
                    {
                        int DisconnectedID = (int)(uintptr_t)event.peer->data;
                        cout << "player " << DisconnectedID << " disconnected" << endl;
                        if(GameStarted) Players[DisconnectedID].CommanderAvalible = 0;
                        else {
                            LocalPlayerCount--;
                            for(size_t i = 0; i < Server->peerCount; ++i) {
                                ENetPeer* Peers = &Server->peers[i];
                                if(Peers->state == ENET_PEER_STATE_CONNECTED) {
                                    int PeersID = (int)(uintptr_t)Peers->data;
                                    if(PeersID > DisconnectedID) {
                                        Peers->data = (void*)(uintptr_t)(PeersID - 1);
                                    }
                                }
                            }
                        }
                        PACKET_PLAYER_DISCONNECT Disjoin;
                        Disjoin.DisconnectedID = DisconnectedID;

                        ENetPacket* disconnect_packet = enet_packet_create(&Disjoin, sizeof(Disjoin), ENET_PACKET_FLAG_RELIABLE);
                        enet_host_broadcast(Server, 0, disconnect_packet);
                        break;
                    }
                    case ENET_EVENT_TYPE_RECEIVE:
                    {
                        Packets* type = (Packets*)event.packet->data;
                        if(*type == PLACE_COMMANDER) {
                            PACKET_COMMANDER_PLACEMENT* commander_placement = (PACKET_COMMANDER_PLACEMENT*)event.packet->data;
                            int Tile = commander_placement->Tile;
                            int ID = commander_placement->PlayerID;
                            PACKET_COMMANDER_PLACEMENT commander_placement_success;
                            commander_placement_success.PlayerID = ID;
                            commander_placement_success.Tile = Tile;
                            if(IsCommanderPlacementOkay(Tile, ID)) {
                                ENetPacket* commander_packet = enet_packet_create(&commander_placement_success, sizeof(commander_placement_success), ENET_PACKET_FLAG_RELIABLE);
                                enet_host_broadcast(Server, 0, commander_packet);
                            }
                        }
                        if(*type == INCREASE_ROUND) {
                            Round++;
                            PACKET_ROUND increase;
                            ENetPacket* increase_packet = enet_packet_create(&increase, sizeof(increase), ENET_PACKET_FLAG_RELIABLE);
                            enet_host_broadcast(Server, 0, increase_packet);
                        }
                        if(*type == BUY_TROOP) {
                            PACKET_BUY_TROOP* buy_troop = (PACKET_BUY_TROOP*)event.packet->data;
                            int Bought = buy_troop->BoughtTroop;
                            int ID = (int)(uintptr_t)event.peer->data;
                            PACKET_BUY_TROOP buy_troop_s;
                            buy_troop_s.BoughtTroop = Bought;
                            buy_troop_s.PlayerID = ID;
                            if(AddBoughtTroopToTheTroopBank(Bought, ID - 1)) {
                                ENetPacket* buy_troop_success = enet_packet_create(&buy_troop_s, sizeof(buy_troop_s), ENET_PACKET_FLAG_RELIABLE);
                                enet_peer_send(event.peer, 0, buy_troop_success);
                                PACKET_ROUND increase;
                                ENetPacket* increase_packet = enet_packet_create(&increase, sizeof(increase), ENET_PACKET_FLAG_RELIABLE);
                                enet_host_broadcast(Server, 0, increase_packet);
                            }
                        }
                        if(*type == PLACE_TROOP) {
                            PACKET_PLACE_TROOP* place = (PACKET_PLACE_TROOP*)event.packet->data;
                            int Tile = place->Tile;
                            int ID = (int)(uintptr_t)event.peer->data;
                            int Slot = place->Slot;
                            troop Troop = place->Troop;
                            PACKET_PLACE_TROOP place_success;
                            place_success.ID = ID;
                            place_success.Tile = Tile;
                            place_success.Troop = Troop;
                            Key = Slot + 1;
                            if(IsPlacementOkay(Tile, ID - 1)) {
                                place_success.Slot = EmptyCounter;
                                ENetPacket* place_packet = enet_packet_create(&place_success, sizeof(place_success), ENET_PACKET_FLAG_RELIABLE);
                                enet_host_broadcast(Server, 0, place_packet);
                            }
                        }
                        if(*type == MOVE_TROOP) {
                            PACKET_MOVE_TROOP* moving = (PACKET_MOVE_TROOP*)event.packet->data;
                            int FromTile = moving->FromTile;
                            int ToTile = moving->ToTile;
                            int ID = (int)(uintptr_t)event.peer->data;
                            for(auto i : moving->Moving) {
                                if(i.second.type != 'e') {
                                    cout << i.first << " " << i.second.type << endl;
                                    MovingTroops[i.first] = i.second;
                                }
                            }
                            if(IsMovingOkay(FromTile, ToTile, ID - 1)) {
                                PACKET_MOVE_TROOP moving_s;
                                moving_s.FromTile = FromTile;
                                moving_s.ToTile = ToTile;
                                moving_s.ID = ID;
                                int index = 0;
                                for(auto i : MovingTroopsCopy) {
                                    moving_s.Moving[index] = {i.first, i.second};
                                    index++;
                                }
                                ENetPacket* move_packet = enet_packet_create(&moving_s, sizeof(moving_s), ENET_PACKET_FLAG_RELIABLE);
                                enet_host_broadcast(Server, 0, move_packet);
                            }
                            MovingTroops.clear();
                            MovingTroopsCopy.clear();
                        }
                        if(*type == DELETE_TROOP) {
                            PACKET_DELETE_TROOP* delete_troop = (PACKET_DELETE_TROOP*)event.packet->data;
                            int Tile = delete_troop->Tile;
                            int Slot = delete_troop->Slot;
                            int ID = (int)(uintptr_t)event.peer->data;
                            PACKET_DELETE_TROOP delete_success;
                            if(DeleteTheTroop(ID - 1, Tile - 1, Slot - 1)) {
                                delete_success.ID = ID;
                                delete_success.Tile = Tile;
                                delete_success.Slot = Slot;
                                delete_success.NewWarPoints = PointDifferance;
                                PointDifferance = 0;
                                TileSelected = 0;
                                Key = 0;
                            }
                            ENetPacket* delete_packet = enet_packet_create(&delete_success, sizeof(delete_success), ENET_PACKET_FLAG_RELIABLE);
                            enet_host_broadcast(Server, 0, delete_packet);
                        }
                        enet_packet_destroy(event.packet);
                        break;
                    }
                }
            }
        }
        else if(LocalPlay && Client != nullptr) { //client
            while (enet_host_service(Client, &event, 0) > 0) {
                switch(event.type) {
                    case ENET_EVENT_TYPE_CONNECT:
                        cout << "Connected succesfully" << endl;
                        InServer = 1;
                        break;
                    case ENET_EVENT_TYPE_DISCONNECT:
                        cout << "Disconnected or server denied us" << endl;
                        LocalPlay = 0;
                        Client = nullptr;
                        Peer = nullptr;
                        HostIP.clear();
                        PlayerCurrent = PLAYER_NONE;
                        InServer = 0;
                        break;
                    case ENET_EVENT_TYPE_RECEIVE:
                    {
                        Packets* type = (Packets*)event.packet->data;
                        if(*type == JOIN_RESPONSE) {
                            PACKET_PLAYER_JOIN* JoiningData = (PACKET_PLAYER_JOIN*)event.packet->data;
                            PlayerID = JoiningData->ID;
                            LocalPlayerCount = JoiningData->CurrentPlayerCount;
                            cout << "My ID: " << PlayerID << "\n" << "Total player count: " << LocalPlayerCount << endl;
                        }
                        if(*type == DISCONNECTED) {
                            PACKET_PLAYER_DISCONNECT* DisconnectingData = (PACKET_PLAYER_DISCONNECT*)event.packet->data;
                            int DisconnectingID = DisconnectingData->DisconnectedID;
                            cout << "ID: " << DisconnectingID << " Disconnected" << endl;
                            if(GameStarted) {
                                Players[DisconnectingID].CommanderAvalible = 0;
                            }
                            else if(PlayerID > DisconnectingID) {
                                LocalPlayerCount--;
                                PlayerID--;
                            }
                        }
                        if(*type == START_GAME) {
                            GameStarted = 1;
                            if(LocalPlayerCount >= 2) {
                                GameStarted = true;
                                Players.clear();
                                Players.push_back(red);
                                Players.push_back(blue); 
                                PlayerCount = LocalPlayerCount;
                            }
                            if(LocalPlayerCount >= 3) {
                                Players.push_back(green);
                            }
                            if(LocalPlayerCount >= 4) {
                                Players.push_back(yellow);
                            }
                            if(LocalPlayerCount >= 5) {
                                Players.push_back(orange);
                            }
                            if(LocalPlayerCount >= 6) {
                                Players.push_back(purple);
                            }
                        }
                        if(*type == PLACE_COMMANDER) {
                            PACKET_COMMANDER_PLACEMENT* commander_placement = (PACKET_COMMANDER_PLACEMENT*)event.packet->data;
                            int Tile = commander_placement->Tile;
                            int ID = commander_placement->PlayerID;
                            Troops[Tile - 1][0] = commander;
                            Troops[Tile - 1][0].side = Players[ID - 1].color;
                            Action = 0;
                            TileSelected = 0;
                            Round++;
                        }
                        if(*type == BUY_TROOP) {
                            PACKET_BUY_TROOP* buy_troop = (PACKET_BUY_TROOP*)event.packet->data;
                            int Bought = buy_troop->BoughtTroop;
                            int ID = buy_troop->PlayerID;
                            for(int i = 0; i < 10; ++i) {
                                if(Players[PlayerID - 1].TroopBank[i].type == empty_troop.type) {
                                    switch(Bought) {
                                        case 1:
                                            Players[PlayerID - 1].TroopBank[i] = infantry;
                                            Players[PlayerID - 1].TroopBank[i].side = Players[PlayerID - 1].color;
                                            break;
                                        case 2:
                                            Players[PlayerID - 1].TroopBank[i] = medic;
                                            Players[PlayerID - 1].TroopBank[i].side = Players[PlayerID - 1].color;
                                            break;
                                        case 3:
                                            Players[PlayerID - 1].TroopBank[i] = artillery;
                                            Players[PlayerID - 1].TroopBank[i].side = Players[PlayerID - 1].color;
                                            break;
                                        case 4:
                                            Players[PlayerID - 1].TroopBank[i] = tank;
                                            Players[PlayerID - 1].TroopBank[i].side = Players[PlayerID - 1].color;
                                            break;
                                        case 5:
                                            Players[PlayerID - 1].TroopBank[i] = plane;
                                            Players[PlayerID - 1].TroopBank[i].side = Players[PlayerID - 1].color;
                                            break;
                                    }
                                    break;
                                }
                                Action = 0;
                                TileSelected = 0;
                            }
                        }
                        if(*type == PLACE_TROOP) {
                            PACKET_PLACE_TROOP* place = (PACKET_PLACE_TROOP*)event.packet->data;
                            int Tile = place->Tile;
                            int ID = place->ID;
                            int Slot = place->Slot;
                            troop Troop = place->Troop;
                            Troops[Tile - 1][Slot] = Troop;
                            Troops[Tile - 1][Slot].side = Players[ID - 1].color;
                            cout << Troop.type << " " << Troop.side << " " << Tile - 1 << " " << Slot << endl;
                            Action = 0;
                            TileSelected = 0;
                            Key = 0;
                            TileSelected = 0;
                            Round++;
                        }
                        if(*type == MOVE_TROOP) {
                            PACKET_MOVE_TROOP* moving = (PACKET_MOVE_TROOP*)event.packet->data;
                            int FromTile = moving->FromTile;
                            int ToTile = moving->ToTile;
                            int ID = moving->ID;
                            cout << "From: " << FromTile << "To: " << ToTile << endl;
                            for(auto i : moving->Moving) {
                                cout << "Troop: " << i.second.type << "Slot: " << i.first << endl;
                                for(int j = 0; j < 10; ++j) {
                                    if(Troops[ToTile - 1][j].type == 'e') {
                                        Troops[ToTile - 1][j] = Troops[FromTile - 1][i.first];
                                        break;
                                    } 
                                }
                                Troops[FromTile - 1][i.first] = empty_troop;
                            }
                            Round++;
                        }
                        if(*type == COMBAT) {
                            PACKET_COMBAT* combat = (PACKET_COMBAT*)event.packet->data;
                            for(int j = 0; j < combat->index; ++j) {
                                if(combat->NewTroopHealths[j].second <= 0) {
                                    Troops[combat->NewTroopHealths[j].first.first][combat->NewTroopHealths[j].first.second] = empty_troop;
                                }
                                else {
                                    Troops[combat->NewTroopHealths[j].first.first][combat->NewTroopHealths[j].first.second].health = combat->NewTroopHealths[j].second;
                                }
                            }
                            for(int j = 0; j < PlayerCount; ++j) {
                                if(Players[j].CommanderAvalible != combat->CommanderAvalibility[j]) {
                                    Players[j].CommanderAvalible = combat->CommanderAvalibility[j];
                                    DeleteEliminatedTroops();
                                }
                            }
                        }
                        if(*type == DELETE_TROOP) {
                            PACKET_DELETE_TROOP* delete_troop = (PACKET_DELETE_TROOP*)event.packet->data;
                            int ID = delete_troop->ID;
                            int Tile = delete_troop->Tile;
                            int Slot = delete_troop->Slot;
                            int NewPoint = delete_troop->NewWarPoints;
                            Troops[Tile - 1][Slot - 1] = empty_troop;
                            if(PlayerID == ID) {
                                Players[ID - 1].WarPoints += NewPoint;
                            }
                            Round++;
                        }
                        if(*type == INCREASE_ROUND) {
                            Round++;
                        }
                        enet_packet_destroy(event.packet);
                        break;
                    }
                }
            }
        }
        if(PlayerCurrent == PLAYER_HOST && Server == nullptr) { //hosting
            Server = enet_host_create(&Host_Address, 6, 1, 0, 0);
            if(Server == nullptr) {
                cout << "A server already exists" << endl;
                PlayerCurrent = PLAYER_NONE;
                LocalPlay = 0;
                continue;
            }
            cout << "Server is ready" << endl;
            LocalPlayerCount = 1;
            PlayerID = 1;
            InServer = 1;
        }
        if(PlayerCurrent == PLAYER_CLIENT && Client == nullptr) { //joining
            Client = enet_host_create(NULL, 1, 2, 0, 0);
            if(Client == nullptr) {
                cout << "Error joining to the server" << endl;
                PlayerCurrent = PLAYER_NONE;
                LocalPlay = 0;
                continue;
            }
            JoiningServer = 1;
        }
        if(JoiningServer) { //joined
            int KeyPressed = GetKeyPressed();
            int CharPressed = GetCharPressed();
            if(KeyPressed == KEY_ENTER) {
                string IP_String(HostIP.begin(), HostIP.end());
                enet_address_set_host(&Client_Address, IP_String.c_str());
                cout << "Connecting to " << IP_String << "..." << endl;
                Peer = enet_host_connect(Client, &Client_Address, 1, 0);
                if(Peer == NULL) {
                    cout << "Can't connect" << endl;
                    PlayerCurrent = PLAYER_NONE;
                    LocalPlay = 0;
                    JoiningServer = 0;
                    continue;
                }
                JoiningServer = 0;
                continue;
            }
            else if(KeyPressed == KEY_ESCAPE) {
                JoiningServer = 0;
                PlayerCurrent = PLAYER_NONE;
                HostIP.clear();
            }
            else if(KeyPressed == KEY_BACKSPACE && !HostIP.empty()) {
                HostIP.pop_back();
            }
            if(CharPressed > 0) HostIP.push_back((char)CharPressed);
        }
        if(TimePlayed < 0.95f) UpdateMusicStream(Intro);
        else PauseMusicStream(Intro);
        TimePlayed = GetMusicTimePlayed(Intro)/GetMusicTimeLength(Intro);
        if(GameStarted && !TroopsCleared) {
            ClearTroops();
            TroopsCleared = 1;
        }
        if(GameStarted && Players[Round % PlayerCount].CommanderAvalible == 0) {
            GhostRounds++;
            Round++;
            continue;
        }
        if(GameStarted) {
            int CommanderCount = 0;
            for(int i = 0; i < PlayerCount; ++i) {
                if(Players[i].CommanderAvalible) {
                    CommanderCount++;
                }
            }
            if(CommanderCount == 1) {
                GameShouldEnd = 1;
            }
            else if(CommanderCount == 0) {
                GameShouldEnd = 1;
                GameDraw = 1;
            }
        }
        float MouseWheel = GetMouseWheelMove();
        if(MouseWheel != 0) {
            GameCamera.zoom += MouseWheel * 0.1f;
            if(GameCamera.zoom < 1.0) GameCamera.zoom = 1.0;
            if(GameCamera.zoom > 3.0) GameCamera.zoom = 3.0;
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
            Vector2 MouseDifferance = GetMouseDelta();

            GameCamera.target.x -= MouseDifferance.x / GameCamera.zoom;
            GameCamera.target.y -= MouseDifferance.y / GameCamera.zoom;
        }
        float ShowingWidth = (screenWidth - MapBorderX) / GameCamera.zoom;
        float ShowingHeight = (screenHeight - MapBorderY) / GameCamera.zoom;

        float MaxX = MapBorderX + Map.width - ShowingWidth;
        float MinX = MapBorderX;
        float MaxY = MapBorderY + Map.height - ShowingHeight;
        float MinY = MapBorderY;
        if (GameCamera.target.x < MinX) GameCamera.target.x = MinX;
        if (GameCamera.target.x > MaxX) GameCamera.target.x = MaxX;
        if (GameCamera.target.y < MinY) GameCamera.target.y = MinY;
        if (GameCamera.target.y > MaxY) GameCamera.target.y = MaxY;
        if(LastRound != Round) {
            CombatHappened = 0;
            LastRound = Round;
            ReArrangeTroops();
        }
        if(!CombatHappened && GameStarted && PlayerCurrent != PLAYER_CLIENT && Round % PlayerCount == 0) {
            Combat(PlayerCurrent);
        }
        ClearMouseCoords();
        MouseClicked = IsMouseButtonPressed(0);
        if(GameStarted && IsKeyPressed(KEY_ESCAPE) && !SettingsScreen && !LoadScreen && !SaveScreen) {
            SettingsScreen = 1;
        }
        else if((GameStarted && IsKeyPressed(KEY_ESCAPE) && SettingsScreen) || LoadScreen || SaveScreen) {
            SettingsScreen = 0;
        }
        if(!GameStarted && IsKeyPressed(KEY_KP_ADD)) {
            if(PlayerCount < 6) {
                PlayerCount++;
            }
        }
        else if (!GameStarted && IsKeyPressed(KEY_KP_SUBTRACT)) {
            if(PlayerCount > 2) {
                PlayerCount--;
            }
        }
        if(LocalPlay && IsKeyPressed(KEY_ESCAPE)) {
            LocalPlay = 0;
            PlayerCurrent = PLAYER_NONE;
            JoiningServer = 0;
            InServer = 0;
            Server = nullptr;
            Client = nullptr;
            Peer = nullptr;
        }
        if(MouseClicked && TimePlayed >= 0.95f) { // Mouse Controls
            GetMouseCoords();
            if(GameStarted && MouseX >= MapBorderX && MouseX <= MapBorderX + Map.width && MouseY >= MapBorderY && MouseY <= MapBorderY + Map.height && !SettingsScreen && !SaveScreen && !LoadScreen) {
                Vector2 MouseCoords = GetScreenToWorld2D(GetMousePosition(), GameCamera);
                MouseX = MouseCoords.x;
                MouseY = MouseCoords.y;
            }
            cout << MouseX << " " << MouseY << endl;
            if(!GameStarted && MouseX >= 1600 && MouseX <= 1900 && MouseY >= 800 && MouseY <= 920 && !CreditScreen && !Restarted && !HowToPlayScreen && !LocalPlay) {
                CreditScreen = 1;
            }
            else if(!GameStarted && MouseX >= 1600 && MouseX <= 1900 && MouseY >= 940 && MouseY <= 1060 && !CreditScreen && !Restarted && !HowToPlayScreen && !LocalPlay) {
                HowToPlayScreen = 1;
            }
            else if(!GameStarted && MouseX >= 200 && MouseX <= 800 && MouseY >= 620 && MouseY <= 820 && !CreditScreen && !Restarted && !HowToPlayScreen && !LocalPlay) {
                CloseTheWindow = 1;
            }
            else if(!GameStarted && MouseX >= 1000 && MouseX <= 1600 && MouseY >= 620 && MouseY <= 820 && !CreditScreen && !Restarted && !HowToPlayScreen) {
                LocalPlay = 1;
            }
            else if(Restarted) {
                Restarted = 0;
            }
            else if(CreditScreen) {
                CreditScreen = 0;
            }
            else if(HowToPlayScreen) {
                HowToPlayScreen = 0;
                Page = 0;
            }
            else if(GameStarted && MouseX >= 800 && MouseX <= 1120 && MouseY >= 600 && MouseY <= 700 && SettingsScreen) {
                CloseTheWindow = 1;
            }
            else if(InServer && !GameStarted && PLAYER_HOST == PlayerCurrent && MouseX >= 200 && MouseX <= 800 && MouseY >= 400 && MouseY <= 600) {
                if(LocalPlayerCount >= 2) {
                    GameStarted = true;
                    Players.clear();
                    Players.push_back(red);
                    Players.push_back(blue); 
                    PACKET_START_THE_GAME GameStart;
                    ENetPacket* start_packet = enet_packet_create(&GameStart, sizeof(GameStart), ENET_PACKET_FLAG_RELIABLE);
                    enet_host_broadcast(Server, 0, start_packet);
                    PlayerCount = LocalPlayerCount;
                }
                else {
                    cout << "at least 2 player needed!" << endl;
                }
                if(LocalPlayerCount >= 3) {
                    Players.push_back(green);
                }
                if(LocalPlayerCount >= 4) {
                    Players.push_back(yellow);
                }
                if(LocalPlayerCount >= 5) {
                    Players.push_back(orange);
                }
                if(LocalPlayerCount >= 6) {
                    Players.push_back(purple);
                }
            }
            else if(LocalPlay && !GameStarted && MouseX >= 200 && MouseX <= 800 && MouseY >= 400 && MouseY <= 600 && PlayerCurrent != PLAYER_CLIENT) {
                PlayerCurrent = PLAYER_HOST;
            }
            else if(LocalPlay && !GameStarted && MouseX >= 1000 && MouseX <= 1600 && MouseY >= 400 && MouseY <= 600 && PlayerCurrent != PLAYER_HOST) {
                PlayerCurrent = PLAYER_CLIENT;
            }
            else if(GameStarted == false && !CreditScreen && !HowToPlayScreen && MouseX >= 200 && MouseX <= 800 && MouseY >= 400 && MouseY <= 600 && !LocalPlay) {
                GameStarted = true;
                PlayerCurrent = PLAYER_HOTSEAT;
                if(PlayerCount >= 2) {
                    Players.clear();
                    Players.push_back(red);
                    Players.push_back(blue);
                }
                if(PlayerCount >= 3) {
                    Players.push_back(green);
                }
                if(PlayerCount >= 4) {
                    Players.push_back(yellow);
                }
                if(PlayerCount >= 5) {
                    Players.push_back(orange);
                }
                if(PlayerCount >= 6) {
                    Players.push_back(purple);
                }
            }
            else if(GameStarted == false && !CreditScreen && !HowToPlayScreen && MouseX >= 1000 && MouseX <= 1600 && MouseY >= 400 && MouseY <= 600 && !LocalPlay) {
                GameStarted = true;
                PlayWithABot = 1;
            }
            if(!MouseCleared && GameStarted) {
                ClearMouseCoords();
                MouseCleared = 1;
            }
        }
        if(PlayerCount > 1 && (Round + 1) % (5 * (PlayerCount - 1)) == 0 && Round > 0) {
            IncreaseControl = 1;
        }
        else {
            IncreaseControl = 0;
            Increased = 0;
        }

        BeginDrawing();
            if(GameStarted && !GameShouldEnd && Round < 9999 + GhostRounds && !SaveScreen && !LoadScreen && !SettingsScreen) { // Game Started
                if(PlayWithABot && Round % 2) {
                    // BotMove();
                }
                ClearBackground(WHITE);
                if(IncreaseControl && !Increased) IncreaseWarPoints();
                BeginMode2D(GameCamera);
                DrawTexture(Map, MapBorderX, MapBorderY, WHITE); // Draw map
                DrawTexture(Show_Map, MapBorderX, MapBorderY, WHITE);
                DrawTroops(Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Red_Icon, Blue_Icon, Low_health, Medium_health, High_health, Full_health, Artillery_Icon, Tank_Icon, Plane_Icon);
                EndMode2D();
                DrawRectangle(0,0,400,1080,WHITE);
                if(PlayerCurrent == PLAYER_HOTSEAT) {
                    DrawActions();
                    DrawTurn(WarPoint);
                    DrawRound(screenWidth - MapBorderX, screenHeight);
                }
                else if(Round % PlayerCount == (PlayerID - 1) && PlayerCurrent >= PLAYER_CLIENT) {
                    DrawActions();
                    DrawTurn(WarPoint);
                    DrawRound(screenWidth - MapBorderX, screenHeight);     
                }
                else if(PlayerCurrent >= PLAYER_CLIENT && Players[PlayerID - 1].CommanderAvalible) {
                    DrawText("Wait for\nyour turn!", 10, 10, 60, RED);
                    DrawRound(screenWidth - MapBorderX, screenHeight); 
                }
                else if(PlayerCurrent >= PLAYER_CLIENT) {
                    DrawText("You are out!", 10, 10, 50, RED);
                    DrawRound(screenWidth - MapBorderX, screenHeight); 
                }
            }
            else if(SettingsScreen && GameStarted) {
                DrawSettingsScreen(Restart, Save, Load);
                if(MouseX >= 800 && MouseX <= 900 && MouseY >= 490 && MouseY <= 590) {
                    Restarted = 1;
                    goto restart;
                }
                else if(MouseX >= 910 && MouseX <= 1010 && MouseY >= 490 && MouseY <= 590) {
                    SaveScreen = 1;
                    for(int i = 0; i < 10; ++i) {
                        SaveName[i] = '\0';
                    }
                }
                else if(MouseX >= 1020 && MouseX <= 1120 && MouseY >= 490 && MouseY <= 590) {
                    LoadScreen = 1;
                }
                else if(MouseX >= 800 && MouseX <= 1120 && MouseY >= 710 && MouseY <= 810 && !ShowBridgeTroops && MouseClicked) {
                    ShowBridgeTroops = 1;
                }
                else if(MouseX >= 800 && MouseX <= 1120 && MouseY >= 710 && MouseY <= 810 && ShowBridgeTroops && MouseClicked) {
                    ShowBridgeTroops = 0;
                }
                else if(ShowTroopsWhenZoomed < 2.9f && IsKeyPressed(KEY_KP_ADD)) {
                    ShowTroopsWhenZoomed += 0.1f;
                }
                else if(ShowTroopsWhenZoomed > 1.0f && IsKeyPressed(KEY_KP_SUBTRACT)) {
                    ShowTroopsWhenZoomed -= 0.1f;
                }
            }
            else if(SaveScreen && Round < 9999 + GhostRounds) {
                ClearBackground(WHITE);
                GameSave();
                Saves();
            }
            else if(LoadScreen && Round < 9999 + GhostRounds) {
                ClearBackground(WHITE);
                GameLoadScreen(Tick, TrashBin);
                LastRound = Round;
            }
            else if (!GameStarted && !GameShouldEnd && Round < 9999 + GhostRounds) { // Title screen
                ClearBackground(WHITE);
                if(TimePlayed < 0.95f) DrawLogoScreen(Logo);
                else if(CreditScreen) DrawCreditsandChangelogScreen();
                else if(HowToPlayScreen) DrawHowToPlayScreen(Infantry_Icon, Medic_Icon, Commander_Icon, Artillery_Icon, Tank_Icon, Plane_Icon);
                else if(!LocalPlay) DrawTitleScreen(Logo);
                else DrawServerScreen();
            }
            else if(GameShouldEnd && Round < 9999 + GhostRounds) {
                if(GameDraw) {
                    ClearBackground(GRAY);
                    DrawText("DRAW!", 800, 400, 100, BLACK);
                    DrawText("Click anywhere to restart", 700, 800, 50, BLACK);
                    if(MouseClicked) {
                        Restarted = 1;
                        goto restart;
                    }  
                }
                else if(Players[0].CommanderAvalible) {
                    ClearBackground(RED);
                    DrawText("RED WON!", 800, 400, 100, BLACK);
                    DrawText("Click anywhere to restart", 700, 800, 50, BLACK);
                    if(MouseClicked) {
                        Restarted = 1;
                        goto restart;
                    }
                }
                else if(Players[1].CommanderAvalible) {
                    ClearBackground(BLUE);
                    DrawText("BLUE WON!", 800, 400, 100, BLACK);
                    DrawText("Click anywhere to restart", 700, 800, 50, BLACK);
                    if(MouseClicked) {
                        Restarted = 1;
                        goto restart;
                    }
                }
                else if(Players[2].CommanderAvalible) {
                    ClearBackground(GREEN);
                    DrawText("GREEN WON!", 800, 400, 100, BLACK);
                    DrawText("Click anywhere to restart", 700, 800, 50, BLACK);
                    if(MouseClicked) {
                        Restarted = 1;
                        goto restart;
                    }
                }
                else if(Players[3].CommanderAvalible) {
                    ClearBackground(YELLOW);
                    DrawText("YELLOW WON!", 800, 400, 100, BLACK);
                    DrawText("Click anywhere to restart", 700, 800, 50, BLACK);
                    if(MouseClicked) {
                        Restarted = 1;
                        goto restart;
                    }
                }
                else if(Players[4].CommanderAvalible) {
                    ClearBackground(ORANGE);
                    DrawText("ORANGE WON!", 800, 400, 100, BLACK);
                    DrawText("Click anywhere to restart", 700, 800, 50, BLACK);
                    if(MouseClicked) {
                        Restarted = 1;
                        goto restart;
                    }
                }
                else if(Players[5].CommanderAvalible) {
                    ClearBackground(PURPLE);
                    DrawText("PURPLE WON!", 800, 400, 100, BLACK);
                    DrawText("Click anywhere to restart", 700, 800, 50, BLACK);
                    if(MouseClicked) {
                        Restarted = 1;
                        goto restart;
                    }
                }
            }
            else {
                ClearBackground(GRAY);
                DrawText("DRAW!\n(Because reached round 10000)", 800, 400, 100, BLACK);
                DrawText("Click anywhere to restart", 700, 800, 50, BLACK);
                if(MouseClicked) {
                    Restarted = 1;
                    goto restart;
                }  
            }

        EndDrawing();
    }
    UnloadImage(Map_png);
    UnloadImage(Infantry_png);
    UnloadImage(Medic_png);
    UnloadImage(WarPoint_png);
    UnloadImage(Tick_png);
    UnloadImage(Commander_png);
    UnloadImage(Logo_png);
    UnloadImage(Empty_png);
    UnloadImage(Red_png);    
    UnloadImage(Blue_png);
    UnloadImage(Low_png);
    UnloadImage(Medium_png);
    UnloadImage(High_png);
    UnloadImage(Full_png);
    UnloadImage(Restart_png);
    UnloadImage(Save_png);
    UnloadImage(Load_png);
    UnloadImage(Trash_png);
    UnloadImage(Artillery_png);
    UnloadImage(Tank_png);
    UnloadImage(Show_png);
    UnloadImage(Plane_png);
    UnloadImage(Trench_png);
    UnloadImage(Field_png);
    UnloadImage(Anti_png);
    UnloadImage(Repair_png);
    UnloadImage(Army_png);
    UnloadImage(Green_png);
    UnloadImage(Yellow_png);
    UnloadImage(Orange_png);
    UnloadImage(Purple_png);
    UnloadTexture(Map);
    UnloadTexture(Infantry_Icon);
    UnloadTexture(Medic_Icon);
    UnloadTexture(WarPoint);
    UnloadTexture(Tick);
    UnloadTexture(Commander_Icon);
    UnloadTexture(Logo);
    UnloadTexture(Empty_Icon);
    UnloadTexture(Red_Icon);
    UnloadTexture(Blue_Icon);
    UnloadTexture(Low_health);
    UnloadTexture(Medium_health);
    UnloadTexture(High_health);
    UnloadTexture(Full_health);
    UnloadTexture(Restart);
    UnloadTexture(Save);
    UnloadTexture(Load);
    UnloadTexture(TrashBin);
    UnloadTexture(Artillery_Icon);
    UnloadTexture(Tank_Icon);
    UnloadTexture(Show_Map);
    UnloadTexture(Plane_Icon);
    UnloadTexture(Trench_Icon);
    UnloadTexture(FieldHospital_Icon);
    UnloadTexture(AntiAir_Icon);
    UnloadTexture(RepairWorkshop_Icon);
    UnloadTexture(ArmyHouse_Icon);
    UnloadTexture(Green);
    UnloadTexture(Yellow);
    UnloadTexture(Orange);
    UnloadTexture(Purple);
    CloseAudioDevice();
    enet_host_destroy(Server);
    CloseWindow();
    return 0;
}