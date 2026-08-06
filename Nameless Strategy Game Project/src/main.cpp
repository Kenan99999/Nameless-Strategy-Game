#include <raylib.h>
#include <bits/stdc++.h>

struct troop {
    char type;
    char side;
    int health;
};
troop commander {
    'c',
    'e',
    1
};
troop empty {
    'e',
    'e',
    0
};
troop infantry {
    'i',
    'e',
    10
};
troop medic {
    'm',
    'e',
    5
};



using namespace std;
bool GameStarted = 0;
int Action = 0;
int RedWarPoints = 10;
int BlueWarPoints = 10;
int PixelX = 0;
int PixelY = 0;
int MouseX = 0;
int MouseY = 0;
int TileSelected = 0;
int Round = 0;
bool MouseClicked = 0;
int Checkbox = 0;
bool IncreaseControl = 0;
bool Increased = 0;
int BoughtTroop = 0;
bool PressedKeyI = 0;
bool PressedKeyM = 0;
const int Infantry_Cost = 5;
const int Medic_Cost = 10;
troop RedTroopBank[10];
troop BlueTroopBank[10];
troop Troops[4][10];
Color MouseColor = {255, 0, 0, 0};
vector<vector<int>> Tiles(4);

const int screenWidth = 650;
const int screenHeight = 400;

int MapBorderX = 150;
int MapBorderY = 0;

// Functions

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
    RedWarPoints += r % 3 + 1;
    r = rand();
    BlueWarPoints += r % 3 + 1;
    Increased = 1;
    cout << RedWarPoints << " " << BlueWarPoints << endl;
    return;
}
void TroopBuying(Texture2D Tick) {
    if(IsKeyPressed(KEY_I)) {
        PressedKeyI = 1;
        PressedKeyM = 0;
        BoughtTroop = 1;
    }
    if(PressedKeyI) {
        DrawTick(Tick, MapBorderX - 130, MapBorderY + 10);
    }
    if(IsKeyPressed(KEY_M)) {
        PressedKeyM = 1;
        PressedKeyI = 0;
        BoughtTroop = 2;
    }
    if(PressedKeyM) {
        DrawTick(Tick, MapBorderX - 130, MapBorderY + 110);
    }
    return;
}
void DrawTroopBuyScreen(Texture2D Infantry_Icon, Texture2D Medic_Icon, Texture2D WarPoint) {
    DrawTexture(Infantry_Icon, MapBorderX - 130, MapBorderY + 10, WHITE);
    DrawTexture(Medic_Icon, MapBorderX - 130, MapBorderY + 110, WHITE);
    DrawTexture(WarPoint, MapBorderX - 40, MapBorderY + 10, WHITE);
    DrawTexture(WarPoint, MapBorderX - 40, MapBorderY + 110, WHITE);
    DrawText(TextFormat("%d", Infantry_Cost), MapBorderX - 70, MapBorderY + 10, 30, BLACK);
    DrawText(TextFormat("%d", Medic_Cost), MapBorderX - 70, MapBorderY + 110, 30, BLACK);
    DrawText("I", MapBorderX - 140, MapBorderY + 10, 15, BLACK);
    DrawText("M", MapBorderX - 145, MapBorderY + 110, 15, BLACK);
    return;
}
int ControlChekcBoxes() { // Yes or No
    if((MouseX >= 10 && MouseX <= 50 && MouseY >= 350 && MouseY <= 390) || IsKeyPressed(KEY_Q)) {
        return 1;
    }
    else if ((MouseX >= 60 && MouseX <= 100 && MouseY >= 350 && MouseY <= 390) || IsKeyPressed(KEY_E)){
        return 2;
    }
    else {
        return 0;
    }
}
void DrawCheckboxes() {
    DrawRectangle(10, 350, 40, 40, GREEN);
    DrawRectangle(60, 350, 40, 40, RED);
    DrawText("Q", 15, 353, 40, BLACK);
    DrawText("E", 65, 353, 40, BLACK);
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
            Troops[i][j] = empty;
        }
    }
    for(int i = 0; i < 10; ++i) {
        RedTroopBank[i] = empty;
        BlueTroopBank[i] = empty;
    }
    return;
}
void DrawTurn(int Map_width, int Map_height, Texture2D WarPoint) {
    if(Round % 2 == 0) {
        DrawText("Red's\nturn", MapBorderX + Map_width - 100, MapBorderY + Map_height + 10, 25, RED);
        DrawText(TextFormat("%d", RedWarPoints), MapBorderX + Map_width - 100, MapBorderY + Map_height + 60, 30, RED);
        DrawTexture(WarPoint, MapBorderX + Map_width - 60, MapBorderY + Map_height + 60, WHITE);
    }
    else {
        DrawText("Blue's\nturn", MapBorderX + Map_width - 100, MapBorderY + Map_height + 10, 25, BLUE);
        DrawText(TextFormat("%d", BlueWarPoints), MapBorderX + Map_width - 100, MapBorderY + Map_height + 60, 30, BLUE);
        DrawTexture(WarPoint, MapBorderX + Map_width - 60, MapBorderY + Map_height + 60, WHITE);
    }
    return;
}
void GetMouseCoords() {
    MouseX = GetMouseX();
    MouseY = GetMouseY();
    return;
}
void ChangeTileSelected(Image image, int Map_width, int Map_height) {
    if(MouseX >= MapBorderX && MouseX <= MapBorderX + Map_width && MouseY >= MapBorderY && MouseY <= MapBorderY + Map_height) {
        PixelX = MouseX - MapBorderX;
        PixelY = MouseY - MapBorderY;

        MouseColor = GetImageColor(image, PixelX, PixelY);
        if(ColorIsEqual(MouseColor, {100,0,0,255})) {
            TileSelected = 1;
        }
        else if(ColorIsEqual(MouseColor, {200,0,0,255})) {
            TileSelected = 2;
        }
        else if(ColorIsEqual(MouseColor, {0,100,0,255})) {
            TileSelected = 3;
        }
        else if(ColorIsEqual(MouseColor, {0,200,0,255})) {
            TileSelected = 4;
        }
    }
    return;
}
void DrawTileSelected() {
    switch(TileSelected) { // Tile Selecter
        default:
            DrawText("Select \na \ntile", 10, 10, 30, BLACK);
            break;
        case 1:
            DrawText("Tile 1", 10, 10, 30, MouseColor);
            break;
        case 2:
            DrawText("Tile 2", 10, 10, 30, MouseColor);
            break;
        case 3:
            DrawText("Tile 3", 10, 10, 30, MouseColor);
            break;
        case 4:
            DrawText("Tile 4", 10, 10, 30, MouseColor);
            break;
    }
    return;
}
void CommanderPlacement(Image image, int Map_width, int Map_height) {
    DrawTileSelected();
    if(TileSelected == 0) {
        DrawText("Place your commander", 10, 300, 30, BLACK);
        ChangeTileSelected(image, Map_width, Map_height);
    }
    if(TileSelected != 0) {
        if(MouseClicked) GetMouseCoords();
        DrawCheckboxes();
        Checkbox = ControlChekcBoxes();
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
            if(RedTroopBank[i].type == empty.type) {
                switch(BoughtTroop) {
                    case 1:
                        RedTroopBank[i] = infantry;
                        RedTroopBank[i].side = 'r';
                        RedWarPoints -= 5;
                        if(RedWarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            RedWarPoints += 5;
                            return;
                        }
                        break;
                    case 2:
                        RedTroopBank[i] = medic;
                        RedTroopBank[i].side = 'r';
                        RedWarPoints -= 10;
                        if(RedWarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            RedWarPoints += 5;
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
        cout << "There are no empty spaces for another troop!" << endl;
        BoughtTroop = 0;
        Action = 0;
    }
    else {
        for(int i = 0; i < 10; ++i) {
            if(BlueTroopBank[i].type == empty.type) {
                switch(BoughtTroop) {
                    case 1:
                        BlueTroopBank[i] = infantry;
                        BlueTroopBank[i].side = 'r';
                        BlueWarPoints -= 5;
                        if(BlueWarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            BlueWarPoints += 5;
                            return;
                        }
                        break;
                    case 2:
                        BlueTroopBank[i] = medic;
                        BlueTroopBank[i].side = 'r';
                        BlueWarPoints -= 10;
                        if(BlueWarPoints < 0) {
                            cout << "You don't have enough War Points!" << endl;
                            BlueWarPoints += 10;
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
        cout << "There are no empty spaces for another troop!" << endl;
        BoughtTroop = 0;
        Action = 0;
    }
}
void DrawActions(Image image, int Map_width, int Map_height, Texture2D Infantry_Icon, Texture2D Medic_Icon, Texture2D WarPoint, Texture2D Tick) {
    if(Round == 0 || Round == 1) {
        CommanderPlacement(image, Map_width, Map_height);
    }
    else if(Action == 0) { // Red's Turn and actions
        DrawText("Choose an action", MapBorderX + 10, MapBorderY + Map_height + 10, 20, BLACK);
        DrawRectangle(MapBorderX + 10, MapBorderY + Map_height + 50, 100, 40, GRAY);
        DrawRectangle(MapBorderX + 140, MapBorderY + Map_height + 50, 100, 40, GRAY);
        DrawRectangle(MapBorderX + 270, MapBorderY + Map_height + 50, 100, 40, GRAY);
        DrawText("Buy Troop\n/Skip Round", MapBorderX + 15, MapBorderY + Map_height + 55, 15, BLACK);
        DrawText("Move/Place\nTroop", MapBorderX + 145, MapBorderY + Map_height + 55, 15, BLACK);
        DrawText("Delete\nTroop", MapBorderX + 275, MapBorderY + Map_height + 55, 15, BLACK);
        if(MouseClicked) {
            GetMouseCoords();
            if(MouseX >= MapBorderX + 10 && MouseX <= MapBorderX + 110 && MouseY >= MapBorderY + Map_height + 50 && MouseY <= MapBorderY + Map_height + 90) {
                Action = 1;
            }
            else if(0) {

            }
            else if(0) {

            }
        }

    }
    else if(Action == 1) {
        DrawTroopBuyScreen(Infantry_Icon, Medic_Icon, WarPoint);
        DrawCheckboxes();
        Checkbox = ControlChekcBoxes();
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
}


int main() {
    ClearTroops();
    CreateMapBonds();
    InitWindow(screenWidth, screenHeight, "Nameless Strategy Game");

    // Map and Icons
    Image Tick_png = LoadImage("resources/Yes.png");
    Image Infantry_png = LoadImage("resources/Infantry.png");
    Image Medic_png = LoadImage("resources/Medic.png");
    Image Map_png = LoadImage("resources/map.png"); 
    Image WarPoint_png = LoadImage("resources/Warpoint.png");
    Texture2D Tick = LoadTextureFromImage(Tick_png);
    Texture2D Infantry_Icon = LoadTextureFromImage(Infantry_png);
    Texture2D Medic_Icon = LoadTextureFromImage(Medic_png);
    Texture2D Map = LoadTextureFromImage(Map_png);
    Texture2D WarPoint = LoadTextureFromImage(WarPoint_png);


    SetTargetFPS(60);
     
    while(!WindowShouldClose()) { // Main Game Loop
        ClearMouseCoords();
        MouseClicked = IsMouseButtonPressed(0);

        if(MouseClicked) { // Mouse Controls

            if(GameStarted) {
                GetMouseCoords();
            }

            if(GameStarted == false) {
                GameStarted = true;
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

            ClearBackground(WHITE);

            if(GameStarted) { // Game Started
                if(IncreaseControl && !Increased) IncreaseWarPoints();
                DrawTexture(Map, MapBorderX, MapBorderY, WHITE); // Draw map
                DrawActions(Map_png, Map.width, Map.height, Infantry_Icon, Medic_Icon, WarPoint, Tick);
                DrawTurn(Map.width, Map.height, WarPoint);
                DrawRound(Map.width, Map.height);
            }
            else { // Title screen
                DrawText("Click anywhere to start a game", 20, 200, 38, BLACK);
            }

        EndDrawing();
    }
    UnloadImage(Map_png);
    UnloadImage(Infantry_png);
    UnloadImage(Medic_png);
    UnloadImage(WarPoint_png);
    UnloadImage(Tick_png);
    UnloadTexture(Map);
    UnloadTexture(Infantry_Icon);
    UnloadTexture(Medic_Icon);
    UnloadTexture(WarPoint);
    UnloadTexture(Tick);
    CloseWindow();
    return 0;
}