#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOUSER
#include <bits/stdc++.h>
#include <raylib.h>
#include <enet/enet.h>
struct tagMSG;
typedef struct tagMSG *LPMSG;
using namespace std;
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
struct Player {
    char color;
    troop TroopBank[10];
    bool CommanderAvalible;
    int WarPoints;
};
inline troop commander {
    'c',
    'e',
    1,
    0,
    0,
    0,
    0,
    1
};
inline troop empty_troop {
    'e',
    'e',
    0,
    0,
    0,
    0,
    0,
    0
};
inline troop infantry {
    'i',
    'e',
    10,
    2,
    1,
    0,
    0,
    10
};
inline troop medic {
    'm',
    'e',
    5,
    0,
    1,
    2,
    0,
    5
};
inline troop artillery {
    'a',
    'e',
    15,
    5,
    0,
    0,
    3,
    15
};
inline troop tank{
    't',
    'e',
    30,
    10,
    5,
    0,
    1,
    30
};
inline troop plane {
    'p',
    'e',
    20,
    5,
    2,
    0,
    7,
    20
};
inline building trench{
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
inline building empty_building{
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
inline building field_hospital {
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
inline building anti_air {
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
inline building repair_workshop {
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
inline building army_house {
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
inline Player red {
    'r',
    {empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop},
    1,
    10
};
inline Player blue {
    'b',
    {empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop},
    1,
    10
};
inline Player green {
    'g',
    {empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop},
    1,
    10
};
inline Player yellow {
    'y',
    {empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop},
    1,
    10
};
inline Player orange {
    'o',
    {empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop},
    1,
    10
};
inline Player purple {
    'p',
    {empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop, empty_troop},
    1,
    10
};
inline int PlayerCount = 2;
inline bool GameStarted = 0;
inline int Action = 0;
inline int RedWarPoints = 10;
inline int BlueWarPoints = 10;
inline int PixelX = 0;
inline int PixelY = 0;
inline int MouseX = 0;
inline int MouseY = 0;
inline const int Infantry_Full = 10;
inline const int Medic_Full = 5;
inline const int Artillery_Full = 15;
inline const int Tank_Full = 30;
inline const int Commander_Full = 1;
inline const int Plane_Full = 20;
inline int TileSelected = 0;
inline int FromTileSelected = 0;
inline int ToTileSelected = 0;
inline int Round = 0;
inline bool MouseClicked = 0;
inline int Checkbox = 0;
inline int EmptyCounter = 0;
inline bool IncreaseControl = 0;
inline bool Increased = 0;
inline int BoughtTroop = 0;
inline int BoughtBuilding = 0;
inline bool PressedKeyI = 0;
inline bool PressedKeyM = 0;
inline bool PressedKeyC = 0;
inline bool PressedKeyP = 0;
inline bool TroopChosen = 0;
inline bool IsTileOkay = 1;
inline bool ItIsAnEmptySlot = 0;
inline bool IsCommanderHere = 0;
inline bool CreditScreen = 0;
inline bool MouseCleared = 0;
inline bool CombatHappened = 0;
inline bool SaveScreen = 0;
inline bool LoadScreen = 0;
inline bool HowToPlayScreen = 0;
inline bool PlayWithABot = 0;
inline bool CloseTheWindow = 0;
inline bool SettingsScreen = 0;
inline bool ShowBridgeTroops = 0;
inline int Restarted = 0;
inline int LastRound = 0;
inline int LastClickedX = 0;
inline int LastClickedY = 0;
inline int SelectedSave = 0;
inline int index = 0;
inline int Key;
inline int TempKey;
inline int Page = 0;
inline int GhostRounds = 0;
inline float ShowTroopsWhenZoomed = 1.5f;
inline vector<string> GameSaves;
inline troop MovingTroop;
inline troop SelectedTroop;
inline building BuiltBuilding;
inline Texture2D TempDraw;
inline Texture2D RedBlue;
inline Texture2D Health;
inline Camera2D GameCamera = { 0 };
inline const int Infantry_Cost = 5;
inline const int Medic_Cost = 10;
inline const int Artillery_Cost = 20;
inline const int Tank_Cost = 40;
inline const int Plane_Cost = 30;
inline troop Troops[47][10];
inline building Buildings[47][2];
inline char SaveName[10];
inline Color MouseColor = {255, 0, 0, 0};
inline vector<vector<int>> Tiles(47);
inline vector<pair<int, int>> Centers;
inline vector<string> Terrain(47);
inline vector<string> GameplayTips(2);
inline vector<Player> Players;
inline string SelectedTip;
inline const int screenWidth = 1720;
inline const int screenHeight = 880;

inline const int MapBorderX = 400;
inline const int MapBorderY = 0;

inline const int TileSelector = 0; //Tile Center Selector Mode

inline Image Tick_png ;
inline Image Infantry_png;
inline Image Medic_png ;
inline Image Map_png ;
inline Image WarPoint_png;
inline Image Commander_png;
inline Image Logo_png;
inline Image Empty_png;
inline Image Red_png;
inline Image Blue_png;
inline Image Low_png;
inline Image Medium_png;
inline Image High_png;
inline Image Full_png;
inline Image Restart_png;
inline Image Save_png;
inline Image Load_png;
inline Image Trash_png;
inline Image Artillery_png;
inline Image Tank_png ;
inline Image Show_png;
inline Image Plane_png;
inline Image Trench_png;
inline Image Field_png;
inline Image Anti_png;
inline Image Repair_png;
inline Image Army_png;
inline Image Green_png;
inline Image Yellow_png;
inline Image Orange_png;
inline Image Purple_png;
inline Texture2D Tick;
inline Texture2D Infantry_Icon;
inline Texture2D Medic_Icon;
inline Texture2D Map;
inline Texture2D WarPoint;
inline Texture2D Commander_Icon;
inline Texture2D Logo;
inline Texture2D Empty_Icon;
inline Texture2D Red_Icon;
inline Texture2D Blue_Icon;
inline Texture2D Low_health;
inline Texture2D Medium_health;
inline Texture2D High_health;
inline Texture2D Full_health;
inline Texture2D Restart;
inline Texture2D Save;
inline Texture2D Load;
inline Texture2D TrashBin;
inline Texture2D Artillery_Icon;
inline Texture2D Tank_Icon;
inline Texture2D Show_Map;
inline Texture2D Plane_Icon;
inline Texture2D Trench_Icon;
inline Texture2D FieldHospital_Icon;
inline Texture2D AntiAir_Icon;
inline Texture2D RepairWorkshop_Icon;
inline Texture2D ArmyHouse_Icon;
inline Texture2D Green;
inline Texture2D Yellow;
inline Texture2D Orange;
inline Texture2D Purple;
// buynları resatarta ekle
inline ENetHost* Server = nullptr;
inline ENetHost* Client = nullptr;
inline ENetPeer* Peer = nullptr;
inline int LocalPlayerCount = 0;
inline map<int, troop> MovingTroops;
inline map<int, troop> MovingTroopsCopy;
inline vector<int> Ticks;
inline int PointDifferance;