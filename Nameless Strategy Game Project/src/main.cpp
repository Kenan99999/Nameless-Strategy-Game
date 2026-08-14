#include <raylib.h>
#include <bits/stdc++.h>
struct troop {
    char type;
    char side;
    float health;
    float attack;
    float defense;
    float heal;
    float air_attack;
    float max_health;
};
struct building {
    char type;
    char WhoBuiltIt;
    float health;
    float Attack;
    float Defense;
    float AirAttack;
    float Heal;
    float Repair;
    float max_health;
    int cost;
};
troop commander {
    'c',
    'e',
    1,
    0,
    0,
    0,
    0,
    1
};
troop empty_troop {
    'e',
    'e',
    0,
    0,
    0,
    0,
    0,
    0
};
troop infantry {
    'i',
    'e',
    10,
    2,
    1,
    0,
    0,
    10
};
troop medic {
    'm',
    'e',
    5,
    0,
    1,
    2,
    0,
    5
};
troop artillery {
    'a',
    'e',
    15,
    5,
    0,
    0,
    3,
    15
};
troop tank{
    't',
    'e',
    30,
    10,
    5,
    0,
    1,
    30
};
troop plane {
    'p',
    'e',
    20,
    5,
    2,
    0,
    7,
    20
};
building trench{
    't',
    'e',
    5,
    1,
    1.3,
    1,
    0,
    0,
    5,
    10
};
building empty_building{
    'e',
    'e',
    0,
    1,
    1,
    1,
    0,
    0,
    0,
    0
};
building field_hospital {
    'f',
    'e',
    5,
    1,
    1,
    1,
    5,
    0,
    5,
    10
};
building anti_air {
    'a',
    'e',
    5,
    1,
    1,
    1.3,
    0,
    0,
    5,
    15
};
building repair_workshop {
    'r',
    'e',
    10,
    1,
    1,
    1,
    0,
    5,
    10,
    20
};
building army_house {
    'h',
    'e',
    10,
    1.3,
    1,
    1,
    0,
    0,
    10,
    15
};

using namespace std;
using namespace filesystem;
// Variables
bool GameStarted = 0;
int Action = 0;
int RedWarPoints = 10;
int BlueWarPoints = 10;
int PixelX = 0;
int PixelY = 0;
int MouseX = 0;
int MouseY = 0;
const int Infantry_Full = 10;
const int Medic_Full = 5;
const int Artillery_Full = 15;
const int Tank_Full = 30;
const int Commander_Full = 1;
const int Plane_Full = 20;
int TileSelected = 0;
int FromTileSelected = 0;
int ToTileSelected = 0;
int Round = 0;
bool MouseClicked = 0;
int Checkbox = 0;
int EmptyCounter = 0;
bool IncreaseControl = 0;
bool Increased = 0;
int BoughtTroop = 0;
int BoughtBuilding = 0;
bool PressedKeyI = 0;
bool PressedKeyM = 0;
bool PressedKeyC = 0;
bool PressedKeyP = 0;
bool TroopChosen = 0;
bool IsTileOkay = 1;
bool ItIsAnEmptySlot = 0;
bool IsCommanderHere = 0;
bool CreditScreen = 0;
bool MouseCleared = 0;
bool RedCommanderAvalible = 1;
bool BlueCommanderAvalible = 1;
bool CombatHappened = 0;
bool SaveScreen = 0;
bool LoadScreen = 0;
bool HowToPlayScreen = 0;
bool PlayWithABot = 0;
bool CloseTheWindow = 0;
bool SettingsScreen = 0;
int Restarted = 0;
int LastRound = 0;
int LastClickedX = 0;
int LastClickedY = 0;
int SelectedSave = 0;
int index = 0;
int Key;
int TempKey;
int Page = 0;
vector<string> GameSaves;
troop MovingTroop;
troop SelectedTroop;
building BuiltBuilding;
Texture2D TempDraw;
Texture2D RedBlue;
Texture2D Health;
Camera2D GameCamera = { 0 };
const int Infantry_Cost = 5;
const int Medic_Cost = 10;
const int Artillery_Cost = 20;
const int Tank_Cost = 40;
const int Plane_Cost = 30;
troop RedTroopBank[10];
troop BlueTroopBank[10];
troop Troops[4][10];
building Buildings[4][2];
char SaveName[10];
Color MouseColor = {255, 0, 0, 0};
vector<vector<int>> Tiles(4);
vector<string> Terrain(4);
vector<string> GameplayTips(2);
string SelectedTip;
const int screenWidth = 1920;
const int screenHeight = 1080;

const int MapBorderX = 400;
const int MapBorderY = 0;

const int TileSelector = 0; //TileSelector
Image Trench_png;
Image Field_png;
Image Anti_png;
Image Repair_png;
Image Army_png;
Texture2D Trench_Icon;
Texture2D FieldHospital_Icon;
Texture2D AntiAir_Icon;
Texture2D RepairWorkshop_Icon;
Texture2D ArmyHouse_Icon;
// Functions

void DrawSettingsScreen(Texture2D Restart_Icon, Texture2D Save_Icon, Texture2D Load_Icon) {
    ClearBackground(WHITE);
    DrawRectangle(800, 600, 320, 100, GRAY);
    DrawText("Close the game", 810, 610, 35, BLACK);
    DrawText("Press Esc to return to the game", 600, 10, 60, BLACK);
    DrawTexture(Restart_Icon, 800, 490, WHITE);
    DrawTexture(Save_Icon, 910, 490, WHITE);
    DrawTexture(Load_Icon, 1020, 490, WHITE);
}
void DrawHowToPlayScreen(Texture2D Infantry_Icon, Texture2D Medic_Icon, Texture2D Commander_Icon, Texture2D Artillery_Icon, Texture2D Tank_Icon, Texture2D Plane_Icon) {
    DrawText(TextFormat("Page %d/2", Page + 1), 295, 380, 18, BLACK);
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
        DrawText("<-", 10, 380, 18, BLACK);
        DrawTexture(Commander_Icon, 10, 10, WHITE);
        DrawText("This is commander and every player only have 1 of these.\nThe main goal of the game is to kill the enemy commander.\nCommander stats-> Health:1, Attack:0, Defense:0, Heal:0, Air:0\n(Commander gives a 1,5x attack boost to friendly troops)", 62, 10, 19, BLACK);
        DrawTexture(Infantry_Icon, 10, 90, WHITE);
        DrawText("The cheapest attack option.\nInfantry stats-> Health:10, Attack:2, Defense:1, Heal:0, Air:0", 62, 95, 19, BLACK);
        DrawTexture(Medic_Icon, 10, 150, WHITE);
        DrawText("A troop that heals your army.\nMedic stats-> Health:5, Attack:0, Defense:1, Heal:2, Air:0", 62, 150, 19, BLACK);
        DrawTexture(Artillery_Icon, 10, 210, WHITE);
        DrawText("A strong attack troop.\nArtillery stats-> Health:15, Attack:5, Defense:0, Heal:0, Air:3", 62, 210, 19, BLACK);
        DrawTexture(Tank_Icon, 10, 270, WHITE);
        DrawText("A strong troop for both attack and defense.\nTank stats-> Health:30, Attack:10, Defense:5, Heal:0, Air:1", 62, 270, 19, BLACK);
        DrawTexture(Plane_Icon, 10, 330, WHITE);
        DrawText("Only air attack can damage it and medic can't heal it.\nPlane stats-> Health:20, Attack:5, Defense:2, Heal:0, Air:7", 62, 330, 19, BLACK);
    }
    else if(Page == 0) {
        DrawText("->", 630, 380, 18, BLACK);
        /*DrawText("<-", 10, 380, 18, BLACK);*/
        DrawText("How rounds work: Every round you can only make 1 action\nActions include buying, skipping, moving, placing and deleting\n(Bought troops will be sent into the troop bank waiting for placement)", 10, 10, 18, BLACK);
        DrawText("How warpoints work: Warpoints are the main currency to buy troops.\nIt will increase 1, 2 or 3 randomly every 5 rounds\nand will get a +1 increase every 20 rounds.\n(For instance it will increase 3, 4 or 5 randomly at round 45)", 10, 100, 18, BLACK);
        DrawText("How combat works: Combat happens at the start of every round\nTaken damage will be calculated by the formula enemyattack - yourdefense\nTaken damage will lower you troops health while heal increases it\nAir troops like plane will only be damaged with air attack\n(Combat includes a little bit of randomness for fun)", 10, 200, 18, BLACK);
        DrawText("How tiles work: Each tile has a different terrain\nevery terrain gives certain bonuses and debuffs\nForest: Attack 0.8x, Plains: Defense 0.8x,\nMountains: Attack 0.75x, Defense 1.5x, City: Defense 1.25x", 10, 300, 18, BLACK);
    }
    /*else {
        DrawText("->", 630, 380, 18, BLACK);
        DrawText("48 46 57\n45 65 100 ? ? 100 98 117 ? 108 100 105 ? 115", 10 , 180, 20, BLACK);
        DrawText("?543??5?4535?2432?567?87646????654?243\n????5435?4351?213214325?6546??4??????", 10 , 10, 20, BLACK);
        DrawText("?543??5?45??5435?4351?213214335?243\n??25?6546??4??2432?567?87646????654?????", 10 , 300, 20, BLACK);
    }*/
}
void Saves() {
    if(exists("saves")) {
        for(const auto& file : directory_iterator("saves")) {
            if(file.path().extension() == ".save") {
                if(find(GameSaves.begin(), GameSaves.end(), file.path().filename().string()) == GameSaves.end()) GameSaves.push_back(file.path().filename().string());
            }
        }
    }
}
void GameSave() {
    DrawRectangle(100, 150, 450, 100, GRAY);
    DrawText("File name:\n(Max 10 characters)", 100, 50, 40, BLACK);
    DrawText("Press enter to save\nClick anywhere to cancel", 100, 260, 25, BLACK);
    DrawText(SaveName, 110, 170, 50, BLACK);
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
            File << Round << endl;
            File << RedWarPoints << endl;
            File << BlueWarPoints << endl;
            for(int i = 0; i < 10; ++i) {
                File << RedTroopBank[i].type << endl;
                File << RedTroopBank[i].side << endl;
                File << RedTroopBank[i].health << endl;
                File << RedTroopBank[i].attack << endl;
                File << RedTroopBank[i].defense << endl;
                File << RedTroopBank[i].heal << endl;
                File << RedTroopBank[i].max_health << endl;
            }
            for(int i = 0; i < 10; ++i) {
                File << BlueTroopBank[i].type << endl;
                File << BlueTroopBank[i].side << endl;
                File << BlueTroopBank[i].health << endl;
                File << BlueTroopBank[i].attack << endl;
                File << BlueTroopBank[i].defense << endl;
                File << BlueTroopBank[i].heal << endl;
                File << BlueTroopBank[i].max_health << endl;
            }
            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 10; ++j) {
                    File << Troops[i][j].type << endl;
                    File << Troops[i][j].side << endl;
                    File << Troops[i][j].health << endl;
                    File << Troops[i][j].attack << endl;
                    File << Troops[i][j].defense << endl;
                    File << Troops[i][j].heal << endl;
                    File << Troops[i][j].max_health << endl;
                }
            }
            File << CombatHappened << endl;
            File << PlayWithABot << endl;
            File << Increased << endl;
            for(int i = 0; i < 4; ++i) {
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
    for(int i = 0; i < 4; ++i) {
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
    for(int i = 0;i < 10; ++i) {
        if(RedTroopBank[i].type == 'e') {
            for(int j = i; j < 10; ++j) {
                if(RedTroopBank[j].type != 'e') {
                    RedTroopBank[i] = RedTroopBank[j];
                    RedTroopBank[j] = empty_troop;
                    break;
                }
            }
        }
    }
    for(int i = 0;i < 10; ++i) {
        if(BlueTroopBank[i].type == 'e') {
            for(int j = i; j < 10; ++j) {
                if(BlueTroopBank[j].type != 'e') {
                    BlueTroopBank[i] = BlueTroopBank[j];
                    BlueTroopBank[j] = empty_troop;
                    break;
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
    RedCommanderAvalible = 1;
    BlueCommanderAvalible = 1;
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
void Combat() {
    for(int i = 0; i < 4; ++i) {
        float TotalRedAttack = 0;
        float TotalRedDefense = 0;
        float TotalRedHeal = 0;
        float TakenRedDamage = 0;
        float TotalBlueAttack = 0;
        float TotalBlueDefense = 0;
        float TotalBlueHeal = 0;
        float RedTroopCount = 0;
        float BlueTroopCount = 0;
        float RedCommander = 0;
        float BlueCommander = 0;
        float TakenBlueDamage = 0;
        float RedAirAttack = 0;
        float BlueAirAttack = 0;
        float RedRepair = 0;
        float BlueRepair = 0;
        int BlueBuilding = 0;
        int RedBuilding = 0;
        for(int j = 0; j < 10; ++j) {
            switch(Troops[i][j].side) {
                case 'r':
                    RedBuilding++;
                    TotalRedAttack += Troops[i][j].attack;
                    TotalRedDefense += Troops[i][j].defense;
                    TotalRedHeal += Troops[i][j].heal;
                    RedAirAttack += Troops[i][j].air_attack;
                    if(Troops[i][j].type != 'c') RedTroopCount++;
                    else RedCommander = 1;
                    break;
                case 'b':
                    BlueBuilding++;
                    TotalBlueAttack += Troops[i][j].attack;
                    TotalBlueDefense += Troops[i][j].defense;
                    TotalBlueHeal += Troops[i][j].heal;
                    BlueAirAttack += Troops[i][j].air_attack;
                    if(Troops[i][j].type != 'c') BlueTroopCount++;
                    else BlueCommander = 1;
                    break;
                default:
                    break;
            }
        }
        for(int j = 0; j < 2; ++j) {
            if(Buildings[i][j].type != 'e' && (RedBuilding > BlueBuilding || (RedBuilding == BlueBuilding && Buildings[i][j].WhoBuiltIt == 'r')) && RedBuilding) {
                TotalRedAttack *= Buildings[i][j].Attack;
                TotalRedDefense *= Buildings[i][j].Defense;
                TotalRedHeal += Buildings[i][j].Heal;
                RedAirAttack *= Buildings[i][j].AirAttack;
                RedRepair += Buildings[i][j].Repair;
                cout << "red" << endl;
            }
            if(Buildings[i][j].type != 'e' && (RedBuilding < BlueBuilding || (RedBuilding == BlueBuilding && Buildings[i][j].WhoBuiltIt == 'b')) && BlueBuilding) {
                TotalBlueAttack *= Buildings[i][j].Attack;
                TotalBlueDefense *= Buildings[i][j].Defense;
                TotalBlueHeal += Buildings[i][j].Heal;
                BlueAirAttack *= Buildings[i][j].AirAttack;
                BlueRepair += Buildings[i][j].Repair;
                cout << "blue" << endl;
            }
        }
        if(TotalRedAttack / 3 >= 1.0) TotalRedAttack += (rand() % (int)(TotalRedAttack / 3));
        if(TotalRedDefense / 3 >= 1.0) TotalRedDefense += (rand() % (int)(TotalRedDefense / 3));
        if(TotalRedHeal / 3 >= 1.0) TotalRedHeal += (rand() % (int)(TotalRedHeal / 3));
        if(RedAirAttack / 5 >= 1.0) RedAirAttack += (rand() % (int)(RedAirAttack / 5));
        if(RedRepair / 5 >= 1.0) RedRepair += (rand() % (int)(RedRepair / 5));
        if(TotalBlueAttack / 3 >= 1.0) TotalBlueAttack += (rand() % (int)(TotalBlueAttack / 3));
        if(TotalBlueDefense / 3 >= 1.0) TotalBlueDefense += (rand() % (int)(TotalBlueDefense / 3));
        if(TotalBlueHeal / 3 >= 1.0) TotalBlueHeal += (rand() % (int)(TotalBlueHeal / 3));
        if(BlueAirAttack / 5 >= 1.0) BlueAirAttack += (rand() % (int)(BlueAirAttack / 5));
        if(BlueRepair / 5 >= 1.0) BlueRepair += (rand() % (int)(BlueRepair / 5));
        if(RedCommander) {
            TotalRedAttack *= 1.5;
            RedAirAttack *= 1.5;
        }
        if(BlueCommander) {
            TotalBlueAttack *= 1.5;
            BlueAirAttack *= 1.5;
        }
        if(Terrain[i] == "forest") {
            TotalBlueAttack *= 0.8;
            TotalRedAttack *= 0.8;
        }
        if(Terrain[i] == "city") {
            TotalBlueDefense *= 1.25;
            TotalRedDefense *= 1.25;
        }
        if(Terrain[i] == "mountains") {
            TotalBlueDefense *= 1.5;
            TotalRedDefense *= 1.5;
            TotalBlueAttack *= 0.7;
            TotalRedAttack *= 0.7;
        }
        if(Terrain[i] == "plains") {
            TotalBlueDefense *= 0.8;
            TotalRedDefense *= 0.8;
        }
        if(TotalBlueAttack > TotalRedDefense)  TakenRedDamage = TotalBlueAttack - TotalRedDefense;
        if(TotalRedAttack > TotalBlueDefense) TakenBlueDamage = TotalRedAttack - TotalBlueDefense;
        if(!TakenBlueDamage && RedTroopCount) {
            TakenBlueDamage = 0.1;
        }
        if(!TakenRedDamage && BlueTroopCount) {
            TakenRedDamage = 0.1;
        }
        cout << TakenRedDamage << " " << TakenBlueDamage << "tile: " << i + 1 << endl;
        for(int j = 0; j < 10; ++j) {
            switch(Troops[i][j].side) {
                case 'r':
                    if(TotalRedHeal > 0 && Troops[i][j].type != 'p') {
                        float AvalibleHeal = 0;
                        AvalibleHeal = Troops[i][j].max_health - Troops[i][j].health;
                        cout << TotalRedHeal << endl;
                        if(TotalRedHeal > AvalibleHeal) {
                            TotalRedHeal -= AvalibleHeal;
                            Troops[i][j].health = Troops[i][j].max_health;
                        }
                        else {
                            Troops[i][j].health += AvalibleHeal;
                            TotalRedHeal = 0;
                        }
                    }
                    else if(RedRepair > 0) {
                        float AvalibleHeal = 0;
                        AvalibleHeal = Troops[i][j].max_health - Troops[i][j].health;
                        if(RedRepair > AvalibleHeal) {
                            RedRepair -= AvalibleHeal;
                            Troops[i][j].health = Troops[i][j].max_health;
                        }
                        else {
                            Troops[i][j].health += AvalibleHeal;
                            RedRepair = 0;
                        }
                    }
                    break;
                case 'b':
                    if(TotalBlueHeal > 0 && Troops[i][j].type != 'p') {
                        float AvalibleHeal = 0;
                        AvalibleHeal = Troops[i][j].max_health - Troops[i][j].health;
                        if(TotalBlueHeal > AvalibleHeal) {
                            TotalBlueHeal -= AvalibleHeal;
                            Troops[i][j].health = Troops[i][j].max_health;
                        }
                        else {
                            Troops[i][j].health += AvalibleHeal;
                            TotalBlueHeal = 0;
                        }
                    }
                    else if(BlueRepair > 0) {
                        float AvalibleHeal = 0;
                        AvalibleHeal = Troops[i][j].max_health - Troops[i][j].health;
                        if(BlueRepair > AvalibleHeal) {
                            BlueRepair -= AvalibleHeal;
                            Troops[i][j].health = Troops[i][j].max_health;
                        }
                        else {
                            Troops[i][j].health += AvalibleHeal;
                            BlueRepair = 0;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        if((!BlueTroopCount || !RedTroopCount ) && (!BlueCommander && !RedCommander)) {
            continue;
        }
        for(int j = 0; j < 10; ++j) {
            if(Troops[i][j].type != 'c') {
                switch(Troops[i][j].side) {
                    case 'r':
                        if(Troops[i][j].type != 'p') {
                            if(Troops[i][j].health > TakenRedDamage) {
                                Troops[i][j].health -= TakenRedDamage;
                                TakenRedDamage = 0;
                            }
                            else {
                                TakenRedDamage -= Troops[i][j].health;
                                Troops[i][j] = empty_troop;
                            }
                        }
                        else {
                            if(Troops[i][j].health > BlueAirAttack) {
                                Troops[i][j].health -= BlueAirAttack;
                                BlueAirAttack = 0;
                            }
                            else {
                                BlueAirAttack -= Troops[i][j].health;
                                Troops[i][j] = empty_troop;
                            }
                        }
                        break;
                    case 'b':
                        if(Troops[i][j].type != 'p') {
                            if(Troops[i][j].health > TakenBlueDamage) {
                                Troops[i][j].health -= TakenBlueDamage;
                                TakenBlueDamage = 0;
                            }
                            else {
                                TakenBlueDamage -= Troops[i][j].health;
                                Troops[i][j] = empty_troop;
                            }
                        }
                        else {
                            if(Troops[i][j].health > RedAirAttack) {
                                Troops[i][j].health -= RedAirAttack;
                                RedAirAttack = 0;
                            }
                            else {
                                RedAirAttack -= Troops[i][j].health;
                                Troops[i][j] = empty_troop;
                            }
                        }
                        break;
                }
            }
        }
        if(BlueCommander && TakenBlueDamage) {
            BlueCommanderAvalible = 0;
        }
        if(RedCommander && TakenRedDamage) {
            RedCommanderAvalible = 0;
        }
    }
    CombatHappened = 1;
    return;
}
void DrawCreditsandChangelogScreen() {
    DrawText("Changelog:", 10, 10, 30, BLACK);
    DrawText("Credits:", 360, 10, 30, BLACK);
    DrawText("- Working on UI and Map changes", 10, 70, 25, BLACK);
    DrawText("Main Developer:\nKenan Mert Pamuk\nTextures:\nÖmer Kaymak\n\nMade with:\nC++/Raylib", 360, 70, 25, BLACK);
    DrawText("Version: Pre-alpha 0.10.-1 (not finished version of 0.10)", 10, 360, 30, BLACK);
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
    cout << "ERROR" << endl;
    return Empty_Icon;
}
Texture2D DrawSide(char Side, Texture2D Red_Icon, Texture2D Blue_Icon) {
    switch(Side) {
        case 'r':
            return Red_Icon;
        case 'b':
            return Blue_Icon;
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
        DrawTexture(Trench_Icon, MapBorderX - 130, MapBorderY + 10, WHITE);
        DrawTexture(FieldHospital_Icon, MapBorderX - 130, MapBorderY + 70, WHITE);
        DrawTexture(AntiAir_Icon, MapBorderX - 130, MapBorderY + 130, WHITE);
        DrawTexture(RepairWorkshop_Icon, MapBorderX - 130, MapBorderY + 190, WHITE);
        DrawTexture(ArmyHouse_Icon, MapBorderX - 130, MapBorderY + 250, WHITE);
        DrawTexture(WarPoint, MapBorderX - 30, MapBorderY + 10, WHITE);
        DrawTexture(WarPoint, MapBorderX - 30, MapBorderY + 70, WHITE);
        DrawTexture(WarPoint, MapBorderX - 30, MapBorderY + 130, WHITE);
        DrawTexture(WarPoint, MapBorderX - 30, MapBorderY + 190, WHITE);
        DrawTexture(WarPoint, MapBorderX - 30, MapBorderY + 250, WHITE);
        DrawText(TextFormat("%d", trench.cost), MapBorderX - 70, MapBorderY + 10, 30, BLACK);
        DrawText(TextFormat("%d", field_hospital.cost), MapBorderX - 70, MapBorderY + 70, 30, BLACK);
        DrawText(TextFormat("%d", anti_air.cost), MapBorderX - 70, MapBorderY + 130, 30, BLACK);
        DrawText(TextFormat("%d", repair_workshop.cost), MapBorderX - 70, MapBorderY + 190, 30, BLACK);
        DrawText(TextFormat("%d", army_house.cost), MapBorderX - 70, MapBorderY + 250, 30, BLACK);
        DrawText("T", MapBorderX - 145, MapBorderY + 10, 15, BLACK);
        DrawText("F", MapBorderX - 145, MapBorderY + 70, 15, BLACK);
        DrawText("A", MapBorderX - 145, MapBorderY + 130, 15, BLACK);
        DrawText("R", MapBorderX - 145, MapBorderY + 190, 15, BLACK);
        DrawText("H", MapBorderX - 145, MapBorderY + 250, 15, BLACK);
}
void GetMouseCoords() {
    MouseX = GetMouseX();
    MouseY = GetMouseY();
    return;
}
void DrawTitleScreen(Texture2D Logo) {
    DrawRectangle(200, 400, 600, 200, GRAY);
    DrawRectangle(1000, 400, 600, 200, GRAY);
    DrawText("Play with a friend", 250, 450, 50, BLACK);
    DrawText("Play with a bot", 1050, 450, 50, BLACK);
    DrawText("Version: Pre-alpha 0.10.-1 (not finished version of 0.10)", 10, 1000, 30, BLACK);
    DrawTextureEx(Logo, {10, 10}, 0.0f, 2.0f, WHITE);
    DrawText("NAMELESS GAME", 800, 10, 65, BLACK);
    DrawRectangle(1600, 800, 300, 120, GRAY);
    DrawText("Changelog and\nCredits", 1610, 810, 35, BLACK);
    DrawRectangle(1600, 940, 300, 120, GRAY);
    DrawText("How to play", 1610, 950, 35, BLACK);
}
void DrawLogoScreen(Texture2D Logo) {
    DrawTextureEx(Logo, {460, 10}, 0.0f, 20.0f, WHITE);
}
void DrawTick(Texture2D Tick, int x, int y) {
    DrawTexture(Tick, x, y, WHITE);
    return;
}
void ClearMouseCoords() {
    MouseX = 0;
    MouseY = 0;
    return;
}
void DrawRound(int Map_width, int Map_height) {
    DrawText(TextFormat("Round %d", Round + 1), MapBorderX + Map_width - 170, MapBorderY, 30, BLACK);
    return;
}
void IncreaseWarPoints() {
    int r = rand();
    RedWarPoints += (r % 3 + 1) + (Round / 20);
    r = rand();
    BlueWarPoints += (r % 3 + 1) + (Round / 20);
    Increased = 1;
    cout << RedWarPoints << " " << BlueWarPoints << endl;
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
    if(BoughtBuilding) DrawTick(Tick, MapBorderX - 130, (BoughtBuilding- 1) * 60 + 10);
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
    DrawText("To skip don't buy\nanything and confirm.", 10, 500, 35, BLACK);
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
void CreateMapBonds() {
    Tiles[0].push_back(1);
    Tiles[0].push_back(3);
    Tiles[0].push_back(2);
    Tiles[1].push_back(0);
    Tiles[1].push_back(2);
    Tiles[2].push_back(1);
    Tiles[2].push_back(3);
    Tiles[2].push_back(0);
    Tiles[3].push_back(0);
    Tiles[3].push_back(2);
    return;
}
void ClearTroops() {
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 10; ++j) {
            Troops[i][j] = empty_troop;
        }
    }
    for(int i = 0; i < 10; ++i) {
        RedTroopBank[i] = empty_troop;
        BlueTroopBank[i] = empty_troop;
    }
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 2; ++j) {
            Buildings[i][j] = empty_building;
        }
    }
    return;
}
void DrawTurn(Texture2D WarPoint) {
    if(Round % 2 == 0) {
        DrawText("Red", 300, 970, 40, RED);
        DrawText(TextFormat("%d", RedWarPoints), 290, 1015, 50, RED);
        DrawTextureEx(WarPoint, {335, 1015}, 0.0f, 0.6f, WHITE);
    }
    else {
        DrawText("Blue", 300, 970, 40, BLUE);
        DrawText(TextFormat("%d", BlueWarPoints), 290, 1015, 50, BLUE);
        DrawTextureEx(WarPoint, {335, 1015}, 0.0f, 0.6f, WHITE);
    }
    return;
}
void ChangeTileSelected(Image Map, int Map_width, int Map_height) {
    if(MouseX >= MapBorderX && MouseX <= MapBorderX + Map_width && MouseY >= MapBorderY && MouseY <= MapBorderY + Map_height && MouseClicked) {
        PixelX = MouseX - MapBorderX;
        PixelY = MouseY - MapBorderY;

        MouseColor = GetImageColor(Map, PixelX, PixelY);
        if(MouseColor.r) TileSelected = MouseColor.r / 100;
        else if(MouseColor.g) TileSelected = (MouseColor.g + 200) / 100;
    }
    else if(MouseClicked) {
        TileSelected = 0;
    }
    return;
}
void DrawTileSelected() {
    if(TileSelected == 0) DrawText("Select \na \ntile", 10, 10, 30, BLACK);
    else { 
        DrawText(TextFormat("Tile %d", TileSelected), 10, 10, 30, BLACK);
        DrawText(Terrain[TileSelected - 1].c_str(), 10, 40, 25, BLACK);
    }
}
void CommanderPlacement(Image image, int Map_width, int Map_height) {
    DrawTileSelected();
    if(MouseClicked) ChangeTileSelected(image, Map_width, Map_height);
    DrawText("Select a tile to\nplace your commander\nchoose wisely", MapBorderX + 10, 310, 26, BLACK);
    if(TileSelected != 0) {
        if(MouseClicked) GetMouseCoords();
        DrawCheckboxes();
        Checkbox = ControlCheckboxes();
        if(Checkbox == 1) {
            if(Troops[TileSelected - 1][0].type != 'e') {
                cout << "can't place a commander on enemy tile!" << endl;
                TileSelected = 0;
            }
            else {
                Troops[TileSelected - 1][0] = commander;
                if(Round % 2) Troops[TileSelected - 1][0].side = 'b';
                else Troops[TileSelected - 1][0].side = 'r';
                Round++;
                Action = 0;
                TileSelected = 0;
            }
        }
        else if(Checkbox == 2) {
            TileSelected = 0;
        }
        Checkbox = 0;
    }
}
void AddBoughtTroopToTheTroopBank() {
    if(Round % 2 == 0) {
        for(int i = 0; i < 10; ++i) {
            if(RedTroopBank[i].type == empty_troop.type) {
                switch(BoughtTroop) {
                    case 1:
                        RedTroopBank[i] = infantry;
                        RedTroopBank[i].side = 'r';
                        RedWarPoints -= Infantry_Cost;
                        if(RedWarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            RedWarPoints += Infantry_Cost;
                            return;
                        }
                        break;
                    case 2:
                        RedTroopBank[i] = medic;
                        RedTroopBank[i].side = 'r';
                        RedWarPoints -= Medic_Cost;
                        if(RedWarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            RedWarPoints += Medic_Cost;
                            return;
                        }
                        break;
                    case 3:
                        RedTroopBank[i] = artillery;
                        RedTroopBank[i].side = 'r';
                        RedWarPoints -= Artillery_Cost;
                        if(RedWarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            RedWarPoints += Artillery_Cost;
                            return;
                        }
                        break;
                    case 4:
                        RedTroopBank[i] = tank;
                        RedTroopBank[i].side = 'r';
                        RedWarPoints -= Tank_Cost;
                        if(RedWarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            RedWarPoints += Tank_Cost;
                            return;
                        }
                        break;
                    case 5:
                        RedTroopBank[i] = plane;
                        RedTroopBank[i].side = 'r';
                        RedWarPoints -= Plane_Cost;
                        if(RedWarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            RedWarPoints += Plane_Cost;
                            return;
                        }
                        break;
                    default:
                        break;
                }
                cout << "Bought troop added to slot " << i << endl;
                Round++;
                return;
            }
        }
        cout << "There are no empty_troop spaces for another troop!" << endl;
        BoughtTroop = 0;
        Action = 0;
    }
    else {
        for(int i = 0; i < 10; ++i) {
            if(BlueTroopBank[i].type == empty_troop.type) {
                switch(BoughtTroop) {
                    case 1:
                        BlueTroopBank[i] = infantry;
                        BlueTroopBank[i].side = 'b';
                        BlueWarPoints -= Infantry_Cost;
                        if(BlueWarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            BlueWarPoints += Infantry_Cost;
                            return;
                        }
                        break;
                    case 2:
                        BlueTroopBank[i] = medic;
                        BlueTroopBank[i].side = 'b';
                        BlueWarPoints -= Medic_Cost;
                        if(BlueWarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            BlueWarPoints += Medic_Cost;
                            return;
                        }
                        break;
                    case 3:
                        BlueTroopBank[i] = artillery;
                        BlueTroopBank[i].side = 'b';
                        BlueWarPoints -= Artillery_Cost;
                        if(BlueWarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            BlueWarPoints += Artillery_Cost;
                            return;
                        }
                        break;
                    case 4:
                        BlueTroopBank[i] = tank;
                        BlueTroopBank[i].side = 'b';
                        BlueWarPoints -= Tank_Cost;
                        if(BlueWarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            BlueWarPoints += Tank_Cost;
                            return;
                        }
                        break;
                    case 5:
                        BlueTroopBank[i] = plane;
                        BlueTroopBank[i].side = 'b';
                        BlueWarPoints -= Plane_Cost;
                        if(BlueWarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            BlueWarPoints += Plane_Cost;
                            return;
                        }
                        break;
                    default:
                        break;
                }
                cout << "Bought troop added to slot " << i << endl;
                Round++;
                return;
            }
        }
        cout << "There are no empty_troop spaces for another troop!" << endl;
        BoughtTroop = 0;
        Action = 0;
    }
}
void PlaceScreen(Texture2D Infantry_Icon, Texture2D Medic_Icon, Texture2D Commander_Icon, Texture2D Empty_Icon, Texture2D Tick, Image Map, int Map_width, int Map_height, Texture2D Low_health, Texture2D Medium_health, Texture2D High_health, Texture2D Full_health, Texture2D Artillery_Icon, Texture2D Tank_Icon, Texture2D Plane_Icon) {
    int RedTroopCount = 0;
    int BlueTroopCount = 0;
    if(Round % 2 == 0) {
        if(!TroopChosen) {
            DrawText("Select a troop from\nyour troop bank to place", 10, 600, 29, BLACK);
            for(int i = 0; i < 10; ++i) {
                TempDraw = DrawTroopIcon(RedTroopBank[i].type, Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Artillery_Icon, Tank_Icon, Plane_Icon);
                DrawTexture(TempDraw, (i % 2) * 110 + 10, (i / 2) * 110 + 10, WHITE);
                DrawText(TextFormat("%d", i), (i % 2) * 110 + 90, (i / 2) * 110 + 14, 25, BLACK);
            }
            TempKey = GetKeyPressed() - 47;
            if(TempKey >= 1 && TempKey <= 10) {
                Key = TempKey;
            }
            if(Key > 0) {
                DrawTexture(Tick, ((Key - 1) % 2) * 110 + 10, ((Key - 1) / 2) * 110 + 10, WHITE);
                SelectedTroop = RedTroopBank[Key - 1];
            }
        }
        else {
            ChangeTileSelected(Map, Map_width, Map_height);
            DrawTileSelected();
            if(Checkbox == 1 && TileSelected != 0) {
                for(int i = 0; i < 10; ++i) {
                    if(Troops[TileSelected - 1][i].side == 'b') {
                        IsTileOkay = 0;
                    }
                    if(Troops[TileSelected - 1][i].side == 'r' && Troops[TileSelected - 1][i].type == 'c') {
                        IsCommanderHere = 1;
                    }
                    if(Troops[TileSelected - 1][i].side == 'r') {
                        RedTroopCount++;
                    }
                    else if(Troops[TileSelected - 1][i].type == 'e' && !EmptyCounter) {
                        EmptyCounter = i + 1;
                    }
                }
                if(RedTroopCount >= 5) {
                    IsTileOkay = 0;
                    IsCommanderHere = 0;
                }
                if(!EmptyCounter) {
                    IsTileOkay = 0;
                    IsCommanderHere = 0;
                }
                if(IsTileOkay || IsCommanderHere) {
                    Troops[TileSelected - 1][EmptyCounter - 1] = RedTroopBank[Key - 1];
                    RedTroopBank[Key - 1] = empty_troop;
                    cout << "a(n) " << Troops[TileSelected - 1][EmptyCounter - 1].type << " troop succesfully placed" << endl;
                    Round++;
                    Action = 0;
                    PressedKeyC = 0;
                    PressedKeyP = 0;
                    PressedKeyM = 0;
                    Checkbox = 0;
                    TempKey = 0;
                    TroopChosen = 0;
                    TileSelected = 0;
                    IsTileOkay = 1;
                    IsCommanderHere = 0;
                    EmptyCounter = 0;
                    Key = 0;
                    return;
                }
                else {
                    cout << "Tile is either occupied by the enemy or doesn't have any empty_troop slots" << endl;
                    IsTileOkay = 1;
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
            IsTileOkay = 1;
            IsCommanderHere = 0;
            EmptyCounter = 0;
            Key = 0;
        }
        else if(Checkbox == 1 && (SelectedTroop.type == 'e' || SelectedTroop.type == 'n')) {
            cout << "Please choose an appropriate troop" << endl;
        }
        else if(Checkbox == 1) {
            TroopChosen = 1;
        }
    }
    else {
        if(!TroopChosen) {
            DrawText("Select a troop from\nyour troop bank to place", MapBorderX + 10, MapBorderY + 310, 25, BLACK);
            for(int i = 0; i < 10; ++i) {
                TempDraw = DrawTroopIcon(BlueTroopBank[i].type, Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Artillery_Icon, Tank_Icon, Plane_Icon);
                DrawTexture(TempDraw, MapBorderX - (((i + 1) % 2) * 60 + 75), (i / 2) * 60 + 10, WHITE);
                DrawText(TextFormat("%d", i), MapBorderX - (((i + 1) % 2) * 60 + 84), (i / 2) * 60 + 10, 15, BLACK);
            }
            TempKey = GetKeyPressed() - 47;
            if(TempKey >= 1 && TempKey <= 10) {
                Key = TempKey;
            }
            if(Key > 0) {
                DrawTexture(Tick, MapBorderX - (((Key) % 2) * 60 + 75), ((Key - 1) / 2) * 60 + 10, WHITE);
                SelectedTroop = BlueTroopBank[Key - 1];
            }
        }
        else {
            ChangeTileSelected(Map, Map_width, Map_height);
            DrawTileSelected();
            if(Checkbox == 1 && TileSelected != 0) {
                for(int i = 0; i < 10; ++i) {
                    if(Troops[TileSelected - 1][i].side == 'r') {
                        IsTileOkay = 0;
                    }
                    if(Troops[TileSelected - 1][i].side == 'b' && Troops[TileSelected - 1][i].type == 'c') {
                        IsCommanderHere = 1;
                    }
                    if(Troops[TileSelected - 1][i].side == 'b') {
                        BlueTroopCount++;
                    }
                    else if(Troops[TileSelected - 1][i].type == 'e' && !EmptyCounter) {
                        EmptyCounter = i + 1;
                    }
                }
                if(BlueTroopCount >= 5) {
                    IsTileOkay = 0;
                    IsCommanderHere = 0;  
                }
                if(!EmptyCounter) {
                    IsTileOkay = 0;
                    IsCommanderHere = 0;
                }
                if(IsTileOkay || IsCommanderHere) {
                    Troops[TileSelected - 1][EmptyCounter - 1] = BlueTroopBank[Key - 1];
                    BlueTroopBank[Key - 1] = empty_troop;
                    cout << "a(n) " << Troops[TileSelected - 1][EmptyCounter - 1].type << " troop succesfully placed" << endl;
                    Round++;
                    Action = 0;
                    PressedKeyC = 0;
                    PressedKeyP = 0;
                    PressedKeyM = 0;
                    Checkbox = 0;
                    TempKey = 0;
                    TroopChosen = 0;
                    TileSelected = 0;
                    IsTileOkay = 1;
                    EmptyCounter = 0;
                    Key = 0;
                    IsCommanderHere = 0;
                    return;
                }
                else {
                    cout << "Tile is either occupied by the enemy or doesn't have any empty_troop slots" << endl;
                    IsTileOkay = 1;
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
            IsTileOkay = 1;
            EmptyCounter = 0;
            Key = 0;
            IsCommanderHere = 0;
            SelectedTroop.type = 'n';
        }
        else if(Checkbox == 1 && (SelectedTroop.type == 'e' || SelectedTroop.type == 'n')) {
            cout << "Please choose an appropriate troop" << endl;
        }
        else if(Checkbox == 1) {
            TroopChosen = 1;
        }
    }
}
void MoveScreen(Texture2D Infantry_Icon, Texture2D Medic_Icon, Texture2D Commander_Icon, Texture2D Empty_Icon, Texture2D Tick, Image Map, int Map_width, int Map_height, Texture2D Red_Icon, Texture2D Blue_Icon, Texture2D Low_health, Texture2D Medium_health, Texture2D High_health, Texture2D Full_health, Texture2D Artillery_Icon, Texture2D Tank_Icon, Texture2D Plane_Icon) {
    int RedTroopCount = 0;
    int BlueTroopCount = 0;
    if(!FromTileSelected) {
        DrawText("Select a tile to move a troop\nfrom that tile", MapBorderX + 10, MapBorderY + 310, 25, BLACK);
        ChangeTileSelected(Map, Map_width, Map_height);
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
                DrawText(TextFormat("%d", i), ((i % 2) * 110 + 90), (i / 2) * 110 + 14, 25, BLACK);
                TempKey = GetKeyPressed() - 47;
                if(TempKey >= 1 && TempKey <= 10) {
                    Key = TempKey;
                }
                if(Checkbox == 1 && !(MovingTroop.type == 'n')) {
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
                    return;
                }
                DrawCheckboxes();
                Checkbox = ControlCheckboxes();
            }
            if(Key > 0 && Key < 11) {
                DrawTexture(Tick, ((Key - 1) % 2) * 110 + 10, ((Key - 1) / 2) * 110 + 10, WHITE);
                MovingTroop = Troops[FromTileSelected - 1][Key - 1];
            }
            for(int i = 0; i < 2; ++i) {
                TempDraw = DrawBuildingIcon(Buildings[FromTileSelected - 1][i].type, Empty_Icon);
                DrawTexture(TempDraw, MapBorderX + 10 + i * 60, MapBorderY + Map.height + 10, WHITE);
            }
        }
        else {
            if(Round % 2 == 0) {
                if(MovingTroop.side == 'b') {
                    cout << "You can't move an enemy troop" << endl;
                    TroopChosen = 0;
                }
                else if(MovingTroop.side == 'e') {
                    cout << "That slot is empty_troop!" << endl;
                    TroopChosen = 0;
                }
            }
            else {
                if(MovingTroop.side == 'r') {
                    cout << "You can't move an enemy troop" << endl;
                    TroopChosen = 0;
                }
                else if(MovingTroop.side == 'e') {
                    cout << "That slot is empty_troop!" << endl;
                    TroopChosen = 0;
                } 
            }
            if(TroopChosen) {
                IsTileOkay = 0;
                DrawTileSelected();
                ChangeTileSelected(Map, Map_width, Map_height);
                DrawCheckboxes();
                Checkbox = ControlCheckboxes();
                if(Checkbox == 1) {
                    ToTileSelected = TileSelected;
                    if(ToTileSelected) {
                        for(auto i : Tiles[ToTileSelected - 1]) {
                            if(i == FromTileSelected - 1) {
                                cout << i << " "  << FromTileSelected - 1 << endl;
                                IsTileOkay = 1;
                                break;
                            }
                        }
                        for(int i = 0; i < 10; ++i) {
                            if(Troops[ToTileSelected - 1][i].side == 'r') {
                                RedTroopCount++;
                            }
                            else if(Troops[ToTileSelected - 1][i].side == 'b') {
                                BlueTroopCount++;
                            }
                        }
                        if(Round % 2 && BlueTroopCount >= 5) {
                            IsTileOkay = 0;
                        }
                        else if(!(Round % 2) && RedTroopCount >= 5) {
                            IsTileOkay = 0;
                        }
                    }
                    if(IsTileOkay) {
                        for(int i = 0; i < 10; ++i) {
                            if(Troops[ToTileSelected - 1][i].type == 'e') {
                                Troops[FromTileSelected - 1][Key - 1] = empty_troop;
                                Troops[ToTileSelected - 1][i] = MovingTroop;
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
                                return;
                            }
                        }
                        IsTileOkay = 0;
                        cout << "Tile is full" << endl;
                        Checkbox = 0;
                    }
                    else {
                        cout << "You can't move troops more or less than 1 tile" << endl;
                        Checkbox = 0;
                    }
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
void DrawMoveandPlaceTroopsScreen(Texture2D Infantry_Icon, Texture2D Medic_Icon, Texture2D Commander_Icon, Texture2D Empty_Icon, Texture2D Tick, Image Map, int Map_width, int Map_height, Texture2D Red_Icon, Texture2D Blue_Icon, Texture2D Low_health, Texture2D Medium_health, Texture2D High_health, Texture2D Full_health, Texture2D Artillery_Icon, Texture2D Tank_Icon, Texture2D Plane_Icon) {
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
        DrawText("Press M to move a troop\nPress P to place a troop\nPress C to cancel", 10, 10, 25, BLACK);
    }
    if(PressedKeyP) {
        PlaceScreen(Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Tick, Map, Map_width, Map_height, Low_health, Medium_health, High_health, Full_health, Artillery_Icon, Tank_Icon, Plane_Icon);
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
        MoveScreen(Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Tick, Map, Map_width, Map_height, Red_Icon, Blue_Icon, Low_health, Medium_health, High_health, Full_health, Artillery_Icon, Tank_Icon, Plane_Icon);
    }
}
void DrawDeleteTroopsScreen(Image Map, Texture2D Infantry_Icon, Texture2D Medic_Icon, Texture2D WarPoint, Texture2D Tick, Texture2D Commander_Icon, Texture2D Empty_Icon, Texture2D Red_Icon, Texture2D Blue_Icon, Texture2D Low_health, Texture2D Medium_health, Texture2D High_health, Texture2D Full_health, Texture2D Artillery_Icon, Texture2D Tank_Icon, Texture2D Plane_Icon) {
    if(TileSelected == 0) {
        DrawTileSelected();
        ChangeTileSelected(Map, Map.width, Map.height);
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
            if(Round % 2 == 0) {
                if(Troops[TileSelected - 1][Key - 1].side == 'b') {
                    cout << "You can't delete an enemy troop" << endl;
                    TroopChosen = 0;
                }
                else if(Troops[TileSelected - 1][Key - 1].side == 'e') {
                    cout << "That's an empty_troop slot!" << endl;
                    TroopChosen = 0;
                }
                else if(Troops[TileSelected - 1][Key - 1].type == 'c') {
                    cout << "You can't delete your commander!" << endl;
                    TroopChosen = 0;
                }
                else if(Troops[TileSelected - 1][Key - 1].side == 'r') {
                    int First = 0;
                    int MaxHealth = 0;
                    switch(Troops[TileSelected - 1][Key - 1].type) {
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
                        default:
                            break;
                    }
                    RedWarPoints += (First * 6 / 10) * (Troops[TileSelected - 1][Key - 1].health / MaxHealth);
                    Round++;
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
                if(Troops[TileSelected - 1][Key - 1].side == 'r') {
                    cout << "You can't delete an enemy troop" << endl;
                    TroopChosen = 0;
                }
                else if(Troops[TileSelected - 1][Key - 1].side == 'e') {
                    cout << "That's an empty_troop slot!" << endl;
                    TroopChosen = 0;
                }
                else if(Troops[TileSelected - 1][Key - 1].type == 'c') {
                    cout << "You can't delete your commander!" << endl;
                    TroopChosen = 0;
                }
                else if(Troops[TileSelected - 1][Key - 1].side == 'b') {
                    int First = 0;
                    int MaxHealth = 0;
                    switch(Troops[TileSelected - 1][Key - 1].type) {
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
                        default:
                            break;
                    }
                    BlueWarPoints += (First * 6 / 10) * (Troops[TileSelected - 1][Key - 1].health / MaxHealth);
                    Round++;
                    TroopChosen = 0;
                    ItIsAnEmptySlot = 0;
                    Action = 0;
                    Checkbox = 0;
                    TileSelected = 0;
                    Key = 0;
                    return;
                }
            }
        }
    }
    return;
}
void DrawBuildScreen(Image Map, Texture2D Empty_Icon, Texture2D WarPoint, Texture2D Tick) {
    if(!TileSelected) {
        ChangeTileSelected(Map, Map.width, Map.height);
        DrawTileSelected();
        DrawText("Choose a tile to build", MapBorderX + 10, MapBorderY + Map.height + 10, 30, BLACK);
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
            if(IsTileOkay) {
                IsTileOkay = 0;
                if(Round % 2 == 0) {
                    for(int i = 0; i < 10; ++i) {
                        if(Troops[TileSelected - 1][i].side == 'r') {
                            IsTileOkay = 1;
                            break;
                        }
                    }
                }
                else {
                    for(int i = 0; i < 10; ++i) {
                        if(Troops[TileSelected - 1][i].side == 'b') {
                            IsTileOkay = 1;
                            break;
                        }
                    }
                }
                if(Round % 2 == 0 && RedWarPoints >= BuiltBuilding.cost && IsTileOkay) {
                    Buildings[TileSelected - 1][Slot] = BuiltBuilding;
                    Buildings[TileSelected - 1][Slot].WhoBuiltIt = 'r';
                    RedWarPoints -= BuiltBuilding.cost;
                    BoughtBuilding = 0;
                    TileSelected = 0;
                    Action = 0;
                    IsTileOkay = 1;
                    Round++;
                }
                else if(Round % 2 && BlueWarPoints >= BuiltBuilding.cost && IsTileOkay) {
                    Buildings[TileSelected - 1][Slot] = BuiltBuilding;
                    Buildings[TileSelected - 1][Slot].WhoBuiltIt = 'b';
                    BlueWarPoints -= BuiltBuilding.cost;
                    BoughtBuilding = 0;
                    TileSelected = 0;
                    Action = 0;
                    IsTileOkay = 1;
                    Round++;
                }
                else {
                    cout << "You don't have any troops on that tile or you don't have enough money" << endl;
                }
            }
            else {
                cout << "Tile is not okay!" << endl;
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
void DrawActions(Image Map, int Map_width, int Map_height, Texture2D Infantry_Icon, Texture2D Medic_Icon, Texture2D WarPoint, Texture2D Tick, Texture2D Commander_Icon, Texture2D Empty_Icon, Texture2D Red_Icon, Texture2D Blue_Icon, Texture2D Low_health, Texture2D Medium_health, Texture2D High_health, Texture2D Full_health, Texture2D Artillery_Icon, Texture2D Tank_Icon, Texture2D Plane_Icon) {
    if(Round == 0 || Round == 1) {
        CommanderPlacement(Map, Map_width, Map_height);
    }
    else if(Action == 0) { // Red's Turn and actions
        DrawText("Choose an action", MapBorderX + 10, MapBorderY + Map_height + 10, 20, BLACK);
        DrawRectangle(10, 10, 185, 80, GRAY);
        DrawRectangle(10, 100, 185, 80, GRAY);
        DrawRectangle(205, 10, 185, 80, GRAY);
        DrawRectangle(205, 100, 185, 80, GRAY);
        DrawText("Buy Troop\n/Skip Round", 15, 10, 25, BLACK);
        DrawText("Move/Place\nTroop", 15, 105, 25, BLACK);
        DrawText("Delete\nTroop", 210, 15, 25, BLACK);
        DrawText("Build\na building", 210, 105, 25, BLACK);
        DrawText(SelectedTip.c_str(), 10, 200, 30, BLACK);
        if(MouseClicked) {
            GetMouseCoords();
            if(MouseX >= 10 && MouseX <= 195 && MouseY >= 10 && MouseY <= 90) {
                Action = 1;
                SelectedTip = GameplayTips[GetRandomValue(0,1)];
            }
            else if(MouseX >= 205 && MouseX <= 390 && MouseY >= 10 && MouseY <= 90) {
                Action = 3;
                SelectedTip = GameplayTips[GetRandomValue(0,1)];
            }
            else if(MouseX >= 10 && MouseX <= 195 && MouseY >= 100 && MouseY <= 180) {
                Action = 2;
                SelectedTip = GameplayTips[GetRandomValue(0,1)];
            }
            else if(MouseX >= 205 && MouseX <= 390 && MouseY >= 100 && MouseY <= 180) {
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
                AddBoughtTroopToTheTroopBank();
                Action = 0;
                Checkbox = 0;
                BoughtTroop = 0;
                PressedKeyI = 0;
                PressedKeyM = 0;
            }
            else {
                Round++;
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
        DrawMoveandPlaceTroopsScreen(Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Tick, Map, Map_width, Map_height, Red_Icon, Blue_Icon, Low_health, Medium_health, High_health, Full_health, Artillery_Icon, Tank_Icon, Plane_Icon);
    }
    else if(Action == 3) {
        DrawDeleteTroopsScreen(Map, Infantry_Icon, Medic_Icon, WarPoint, Tick, Commander_Icon, Empty_Icon, Red_Icon, Blue_Icon, Low_health, Medium_health, High_health, Full_health, Artillery_Icon, Tank_Icon, Plane_Icon);
    }
    else if(Action == 4) {
        DrawBuildScreen(Map, Empty_Icon, WarPoint, Tick);
    }
}
void GameLoadScreen(Texture2D Tick, Texture2D TrashBin) {
    for(int i = 0; i < 10; ++i) {
        DrawRectangle((i / 5) * 300 + 50, (i % 5) * 60 + 20, 250, 50, GRAY);
        DrawText(TextFormat("%d", i), (i / 5) * 300 + 52, (i % 5) * 60 + 22, 18, BLACK);
        if(GameSaves.size() > i) {
            string ShowingName = path(GameSaves[i]).stem().string();
            DrawText(ShowingName.c_str(), (i / 5) * 300 + 55, (i % 5) * 60 + 45, 25, BLACK);
        }
    }
    TempKey = GetKeyPressed() + 1;
    if(TempKey >= 49 && TempKey <= 58) SelectedSave = TempKey - 48;
    if(SelectedSave > 0) DrawTick(Tick, ((SelectedSave - 1) / 5) * 300 + 250, ((SelectedSave - 1) % 5) * 60 + 20);
    DrawCheckboxes();
    Checkbox = ControlCheckboxes();
    DrawTexture(TrashBin, 605, 355, WHITE);
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
                    File >> Round;
                    File >> RedWarPoints;
                    File >> BlueWarPoints;
                    for(int i = 0; i < 10; ++i) {
                        File >> RedTroopBank[i].type;
                        File >> RedTroopBank[i].side;
                        File >> RedTroopBank[i].health;
                        File >> RedTroopBank[i].attack;
                        File >> RedTroopBank[i].defense;
                        File >> RedTroopBank[i].heal;
                        File >> RedTroopBank[i].max_health;
                    }
                    for(int i = 0; i < 10; ++i) {
                        File >> BlueTroopBank[i].type;
                        File >> BlueTroopBank[i].side;
                        File >> BlueTroopBank[i].health;
                        File >> BlueTroopBank[i].attack;
                        File >> BlueTroopBank[i].defense;
                        File >> BlueTroopBank[i].heal;
                        File >> BlueTroopBank[i].max_health;
                    }
                    for(int i = 0; i < 4; ++i) {
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
    if(MouseClicked && MouseX >= 605 && MouseX <= 645 && MouseY >= 355 && MouseY <= 395 && SelectedSave > 0 && SelectedSave - 1 < GameSaves.size()) {
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
void BotMove() {
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
}
void DrawTroops(Texture2D Infantry_Icon, Texture2D Medic_Icon, Texture2D Commander_Icon, Texture2D Empty_Icon, Texture2D Red_Icon, Texture2D Blue_Icon, Texture2D Low_health, Texture2D Medium_health, Texture2D High_health, Texture2D Full_health, Texture2D Artillery_Icon, Texture2D Tank_Icon, Texture2D Plane_Icon) { // bu fonksiyonu şimdilik elimle koordinat girerek yaptım sonra dosyadan orta noktaları çeken bir sistem haline getireceğim.
    for(int i = 0; i < 10; ++i) {
        TempDraw = DrawTroopIcon(Troops[3][i].type, Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Artillery_Icon, Tank_Icon, Plane_Icon);
        Health = DrawTroopHealth(Troops[3][i].health, Troops[3][i].type, Low_health, Medium_health, High_health, Full_health);

        DrawTextureEx(TempDraw, {(float)(i % 5) * 25 + 203, (float)(i / 5) * 25 + 38}, 0, 0.4, WHITE);
        if(Troops[3][i].type != 'e') {
            RedBlue = DrawSide(Troops[3][i].side, Red_Icon, Blue_Icon);
            DrawTextureEx(Health, {(float)(i % 5) * 25 + 204, (float)(i / 5) * 25 + 55}, 0, 0.4, WHITE);
            DrawTextureEx(RedBlue, {(float)(i % 5) * 25 + 203, (float)(i / 5) * 25 + 38}, 0, 0.4, WHITE);
        }
    }
    for(int i = 0; i < 2; ++i) {
        TempDraw = DrawBuildingIcon(Buildings[3][i].type, Empty_Icon);
        DrawTextureEx(TempDraw, {(float)i * 25 + 203, 93 - 5}, 0, 0.4, WHITE);
    }
    for(int i = 0; i < 10; ++i) {
        TempDraw = DrawTroopIcon(Troops[0][i].type, Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Artillery_Icon, Tank_Icon, Plane_Icon);
        Health = DrawTroopHealth(Troops[0][i].health, Troops[0][i].type, Low_health, Medium_health, High_health, Full_health);

        DrawTextureEx(TempDraw, {(float)(i % 5) * 25 + 186, (float)(i / 5) * 25 + 194}, 0, 0.4, WHITE);
        if(Troops[0][i].type != 'e') {
            RedBlue = DrawSide(Troops[0][i].side, Red_Icon, Blue_Icon);
            DrawTextureEx(Health, {(float)(i % 5) * 25 + 187, (float)(i / 5) * 25 + 211}, 0, 0.4, WHITE);
            DrawTextureEx(RedBlue, {(float)(i % 5) * 25 + 186, (float)(i / 5) * 25 + 194}, 0, 0.4, WHITE);
        }
    }
    for(int i = 0; i < 2; ++i) {
        TempDraw = DrawBuildingIcon(Buildings[0][i].type, Empty_Icon);
        DrawTextureEx(TempDraw, {(float)i * 25 + 186, 249 - 5}, 0, 0.4, WHITE);
    }
    for(int i = 0; i < 10; ++i) {
        TempDraw = DrawTroopIcon(Troops[1][i].type, Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Artillery_Icon, Tank_Icon, Plane_Icon);
        Health = DrawTroopHealth(Troops[1][i].health, Troops[1][i].type, Low_health, Medium_health, High_health, Full_health);

        DrawTextureEx(TempDraw, {(float)(i % 5) * 25 + 464, (float)(i / 5) * 25 + 197}, 0, 0.4, WHITE);
        if(Troops[1][i].type != 'e') {
            RedBlue = DrawSide(Troops[1][i].side, Red_Icon, Blue_Icon);
            DrawTextureEx(Health, {(float)(i % 5) * 25 + 465, (float)(i / 5) * 25 + 214}, 0, 0.4, WHITE);
            DrawTextureEx(RedBlue, {(float)(i % 5) * 25 + 464, (float)(i / 5) * 25 + 197}, 0, 0.4, WHITE);
        }
    }
    for(int i = 0; i < 2; ++i) {
        TempDraw = DrawBuildingIcon(Buildings[1][i].type, Empty_Icon);
        DrawTextureEx(TempDraw, {(float)i * 25 + 464, 252 - 5}, 0, 0.4, WHITE);
    }
    for(int i = 0; i < 10; ++i) {
        TempDraw = DrawTroopIcon(Troops[2][i].type, Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Artillery_Icon, Tank_Icon, Plane_Icon);
        Health = DrawTroopHealth(Troops[2][i].health, Troops[2][i].type, Low_health, Medium_health, High_health, Full_health);

        DrawTextureEx(TempDraw, {(float)(i % 5) * 25 + 440, (float)(i / 5) * 25 + 44}, 0, 0.4, WHITE);
        if(Troops[2][i].type != 'e') {
            RedBlue = DrawSide(Troops[2][i].side, Red_Icon, Blue_Icon);            
            DrawTextureEx(Health, {(float)(i % 5) * 25 + 441, (float)(i / 5) * 25 + 61}, 0, 0.4, WHITE);
            DrawTextureEx(RedBlue, {(float)(i % 5) * 25 + 440, (float)(i / 5) * 25 + 44}, 0, 0.4, WHITE);
        }
    }
    for(int i = 0; i < 2; ++i) {
        TempDraw = DrawBuildingIcon(Buildings[2][i].type, Empty_Icon);
        DrawTextureEx(TempDraw, {(float)i * 25 + 440, 99 - 5}, 0, 0.4, WHITE);
    }
}
void TileCenterSelector() {
    InitWindow(1920, 1080, "Click to tile centers");
    ToggleBorderlessWindowed();
    SetTargetFPS(60);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }
    CloseWindow();
}

int main() {
    if(TileSelector) {
        TileCenterSelector();
    }
    CreateMapBonds();
    InitWindow(screenWidth, screenHeight, "Nameless Strategy Game");
    ToggleBorderlessWindowed();
    // Map and Icons
    Image Tick_png = LoadImage("resources/Yes.png");
    Image Infantry_png = LoadImage("resources/Infantry.png");
    Image Medic_png = LoadImage("resources/Medic.png");
    Image Map_png = LoadImage("resources/map.png");
    Image WarPoint_png = LoadImage("resources/Warpoint.png");
    Image Commander_png = LoadImage("resources/Commander.png");
    Image Logo_png = LoadImage("resources/Logo.png");
    Image Empty_png = LoadImage("resources/Empty.png");
    Image Red_png = LoadImage("resources/Red.png");
    Image Blue_png = LoadImage("resources/Blue.png");
    Image Low_png = LoadImage("resources/Low_health.png");
    Image Medium_png = LoadImage("resources/Medium_health.png");
    Image High_png = LoadImage("resources/High_health.png");
    Image Full_png = LoadImage("resources/Full_health.png");
    Image Restart_png = LoadImage("resources/Restart.png");
    Image Save_png = LoadImage("resources/Save.png");
    Image Load_png = LoadImage("resources/Load.png");
    Image Trash_png = LoadImage("resources/Delete.png");
    Image Artillery_png = LoadImage("resources/Artillery.png");
    Image Tank_png = LoadImage("resources/Tank.png");
    Image Show_png = LoadImage("resources/map_show.png");
    Image Plane_png = LoadImage("resources/Plane.png");
    Trench_png = LoadImage("resources/Trench.png");
    Field_png = LoadImage("resources/Field_Hospital.png");
    Anti_png = LoadImage("resources/Anti_Air.png");
    Repair_png = LoadImage("resources/Repair_Workshop.png");
    Army_png = LoadImage("resources/Army_House.png");
    Texture2D Tick = LoadTextureFromImage(Tick_png);
    Texture2D Infantry_Icon = LoadTextureFromImage(Infantry_png);
    Texture2D Medic_Icon = LoadTextureFromImage(Medic_png);
    Texture2D Map = LoadTextureFromImage(Map_png);
    Texture2D WarPoint = LoadTextureFromImage(WarPoint_png);
    Texture2D Commander_Icon = LoadTextureFromImage(Commander_png);
    Texture2D Logo = LoadTextureFromImage(Logo_png);
    Texture2D Empty_Icon = LoadTextureFromImage(Empty_png);
    Texture2D Red_Icon = LoadTextureFromImage(Red_png);
    Texture2D Blue_Icon = LoadTextureFromImage(Blue_png);
    Texture2D Low_health = LoadTextureFromImage(Low_png);
    Texture2D Medium_health = LoadTextureFromImage(Medium_png);
    Texture2D High_health = LoadTextureFromImage(High_png);
    Texture2D Full_health = LoadTextureFromImage(Full_png);
    Texture2D Restart = LoadTextureFromImage(Restart_png);
    Texture2D Save = LoadTextureFromImage(Save_png);
    Texture2D Load = LoadTextureFromImage(Load_png);
    Texture2D TrashBin = LoadTextureFromImage(Trash_png);
    Texture2D Artillery_Icon = LoadTextureFromImage(Artillery_png);
    Texture2D Tank_Icon = LoadTextureFromImage(Tank_png);
    Texture2D Show_Map = LoadTextureFromImage(Show_png);
    Texture2D Plane_Icon = LoadTextureFromImage(Plane_png);
    Trench_Icon = LoadTextureFromImage(Trench_png);
    FieldHospital_Icon = LoadTextureFromImage(Field_png);
    AntiAir_Icon = LoadTextureFromImage(Anti_png);
    RepairWorkshop_Icon = LoadTextureFromImage(Repair_png);
    ArmyHouse_Icon = LoadTextureFromImage(Army_png);
    Terrain[0] = "forest";
    Terrain[1] = "plains";
    Terrain[2] = "city";
    Terrain[3] = "mountains";
    GameplayTips[0] = "Gameplay\ntip:\nWar Points\nwill increase\nrandomly\nevery\n5 rounds";
    GameplayTips[1] = "Gameplay\ntip:\nMedic can't\nheal a\nplane";
    SelectedTip = GameplayTips[GetRandomValue(0,1)];
    SetTargetFPS(60);
    restart:
    GameCamera.target = {MapBorderX, MapBorderY};
    GameCamera.offset = {MapBorderX, MapBorderY};
    GameCamera.rotation = 0.0f;
    GameCamera.zoom = 1.0f;
    restart();
    ClearTroops();
    Saves();
    SelectedTroop.type = 'n';
    MovingTroop.type = 'n';
    while(!CloseTheWindow) { // Main Game Loop
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
        float MinX = MapBorderX;;
        float MaxY = MapBorderY + Map.height - ShowingHeight;
        float MinY = MapBorderY;
        if (GameCamera.target.x < MinX) GameCamera.target.x = MinX;
        if (GameCamera.target.x > MaxX) GameCamera.target.x = MaxX;
        if (GameCamera.target.y < MinY) GameCamera.target.y = MinY;
        if (GameCamera.target.y > MaxY) GameCamera.target.y = MaxY;
        if(LastRound != Round) {
            CombatHappened = 0;
            LastRound = Round;
        }
        if(!CombatHappened) {
            Combat();
            ReArrangeTroops();
        }
        ClearMouseCoords();
        MouseClicked = IsMouseButtonPressed(0);
        if(GameStarted && IsKeyPressed(KEY_ESCAPE) && !SettingsScreen && !LoadScreen && !SaveScreen) {
            SettingsScreen = 1;
        }
        else if((GameStarted && IsKeyPressed(KEY_ESCAPE) && SettingsScreen) || LoadScreen || SaveScreen) {
            SettingsScreen = 0;
        }
        if(MouseClicked && GetTime() > 4) { // Mouse Controls
            GetMouseCoords();
            if(GameStarted && MouseX >= MapBorderX && MouseX <= MapBorderX + Map.width && MouseY >= MapBorderY && MouseY <= MapBorderY + Map.height && !SettingsScreen && !SaveScreen && !LoadScreen) {
                Vector2 MouseCoords = GetScreenToWorld2D(GetMousePosition(), GameCamera);
                MouseX = MouseCoords.x;
                MouseY = MouseCoords.y;
            }
            cout << MouseX << " " << MouseY << endl;
            if(!GameStarted && MouseX >= 1600 && MouseX <= 1900 && MouseY >= 800 && MouseY <= 920 && !CreditScreen && !Restarted && !HowToPlayScreen) {
                CreditScreen = 1;
            }
            else if(!GameStarted && MouseX >= 1600 && MouseX <= 1900 && MouseY >= 940 && MouseY <= 1060 && !CreditScreen && !Restarted && !HowToPlayScreen) {
                HowToPlayScreen = 1;
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
            else if(GameStarted == false && !CreditScreen && !HowToPlayScreen && MouseX >= 200 && MouseX <= 800 && MouseY >= 400 && MouseY <= 600) {
                GameStarted = true;
            }
            else if(GameStarted == false && !CreditScreen && !HowToPlayScreen && MouseX >= 1000 && MouseX <= 1600 && MouseY >= 400 && MouseY <= 600) {
                GameStarted = true;
                PlayWithABot = 1;
            }
            if(!MouseCleared && GameStarted) {
                ClearMouseCoords();
                MouseCleared = 1;
            }
        }
        if((Round + 1) % 5 == 0 && Round > 0) {
            IncreaseControl = 1;
        }
        else {
            IncreaseControl = 0;
            Increased = 0;
        }
        BeginDrawing();

            if(GameStarted && RedCommanderAvalible && BlueCommanderAvalible && Round < 999 && !SaveScreen && !LoadScreen && !SettingsScreen) { // Game Started
                if(PlayWithABot && Round % 2) {
                    BotMove();
                }
                ClearBackground(WHITE);
                if(IncreaseControl && !Increased) IncreaseWarPoints();
                BeginMode2D(GameCamera);
                DrawTexture(Map, MapBorderX, MapBorderY, WHITE); // Draw map
                DrawTexture(Show_Map, MapBorderX, MapBorderY, WHITE);
                //DrawTroops(Infantry_Icon, Medic_Icon, Commander_Icon, Empty_Icon, Red_Icon, Blue_Icon, Low_health, Medium_health, High_health, Full_health, Artillery_Icon, Tank_Icon, Plane_Icon);
                EndMode2D();
                DrawRectangle(0,0,400,1080,WHITE);
                DrawActions(Map_png, Map.width, Map.height, Infantry_Icon, Medic_Icon, WarPoint, Tick, Commander_Icon, Empty_Icon, Red_Icon, Blue_Icon, Low_health, Medium_health, High_health, Full_health, Artillery_Icon, Tank_Icon, Plane_Icon);
                DrawTurn(WarPoint);
                DrawRound(screenWidth - MapBorderX, screenHeight);
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
            }
            else if(SaveScreen && Round < 999) {
                ClearBackground(WHITE);
                GameSave();
                Saves();
            }
            else if(LoadScreen && Round < 999) {
                ClearBackground(WHITE);
                GameLoadScreen(Tick, TrashBin);
                LastRound = Round;
            }
            else if (RedCommanderAvalible && BlueCommanderAvalible && Round < 999) { // Title screen
                ClearBackground(WHITE);
                if(GetTime() <= 4) DrawLogoScreen(Logo);
                else if(CreditScreen) DrawCreditsandChangelogScreen();
                else if(HowToPlayScreen) DrawHowToPlayScreen(Infantry_Icon, Medic_Icon, Commander_Icon, Artillery_Icon, Tank_Icon, Plane_Icon);
                else DrawTitleScreen(Logo);
            }
            else if(RedCommanderAvalible && !BlueCommanderAvalible && Round < 999) {
                ClearBackground(RED);
                DrawText("RED WON!", 75, 100, 100, BLACK);
                DrawText("Click anywhere to restart", 10, 350, 25, BLACK);
                if(MouseClicked) {
                    Restarted = 1;
                    goto restart;
                }
            }
            else if(!RedCommanderAvalible && BlueCommanderAvalible && Round < 999) {
                ClearBackground(BLUE);
                if(!PlayWithABot) DrawText("BLUE WON!", 50, 100, 100, BLACK);
                else DrawText("BOT WON!", 50, 100, 100, BLACK);
                DrawText("Click anywhere to restart", 10, 350, 25, BLACK);
                if(MouseClicked) {
                    Restarted = 1;
                    goto restart;
                }
            }
            else {
                ClearBackground(GRAY);
                DrawText("DRAW!", 150, 100, 100, BLACK);
                if(Round >= 999) DrawText("You reached round 1000!\nDon't play anymore", 10, 10, 30, BLACK);
                DrawText("Click anywhere to restart", 10, 350, 25, BLACK);
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
    CloseWindow();
    return 0;
}

// NERF WARPOINT INCREASE RATE TOO OP!!!!!!!!!!!!