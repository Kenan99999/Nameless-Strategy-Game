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




using namespace std;
bool GameStarted = 0;
int Action = 0;
int RedWarPoints = 0;
int BlueWarPoints = 0;
int PixelX = 0;
int PixelY = 0;
int MouseX = 0;
int MouseY = 0;
int TileSelected = 0;
int Player = 0;
int Round = 0;
bool MouseClicked = 0;
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

void DrawCheckboxes() {
    DrawRectangle(10, 150, 40, 40, GREEN);
    DrawRectangle(60, 150, 40, 40, RED);
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
}
void ClearTroops() {
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 10; ++j) {
            Troops[i][j] = empty;
        }
    }
}
void DrawTurn(int texture_width, int texture_height) {
    if(Round % 2 == 0) {
        DrawText("Red's\nturn", MapBorderX + texture_width - 100, MapBorderY + texture_height + 10, 30, RED);
    }
    else {
        DrawText("Blue's\nturn", MapBorderX + texture_width - 100, MapBorderY + texture_height + 10, 30, BLUE);
    }
}
void GetMouseCoords() {
    MouseX = GetMouseX();
    MouseY = GetMouseY();
}
void ChangeTileSelected(Image image, int texture_width, int texture_height) {
    if(MouseX >= MapBorderX && MouseX <= MapBorderX + texture_width && MouseY >= MapBorderY && MouseY <= MapBorderY + texture_height) {
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
}
void CommanderPlacement(Image image, int texture_width, int texture_height) {
    DrawTileSelected();
    if(TileSelected == 0) {
        DrawText("Place your commander", 10, 300, 30, BLACK);
        ChangeTileSelected(image, texture_width, texture_height);
    }
    if(TileSelected != 0) {
        if(MouseClicked) GetMouseCoords();
        DrawCheckboxes();
        if(MouseX >= 10 && MouseX <= 50 && MouseY >= 150 && MouseY <= 190) {
            if(Troops[TileSelected - 1][0].type != 'e') {
                cout << "can't place a commander on enemy tile!" << endl;
                TileSelected = 0;
            }
            else {
                cout << "Placed a commander to tile " << TileSelected  << endl;
                Troops[TileSelected - 1][0] = commander;
                if(Round % 2) Troops[TileSelected - 1][0].side = 'b';
                else Troops[TileSelected - 1][0].side = 'r';
                Round++;
                Action = 0;
                TileSelected = 0;
            }
        }
        if(MouseX >= 60 && MouseX <= 100 && MouseY >= 150 && MouseY <= 190) {
            TileSelected = 0;
        }
    }
}
void DrawActions(Image image, int texture_width, int texture_height) {
    if(Round == 0 || Round == 1) {
        CommanderPlacement(image, texture_width, texture_height);
    }
    else if(Action == 0) { // Red's Turn and actions
        DrawText("Choose an action", MapBorderX + 10, MapBorderY + texture_height + 10, 20, BLACK);
        DrawRectangle(MapBorderX + 10, MapBorderY + texture_height + 50, 100, 40, GRAY);
        DrawRectangle(MapBorderX + 140, MapBorderY + texture_height + 50, 100, 40, GRAY);
        DrawRectangle(MapBorderX + 270, MapBorderY + texture_height + 50, 100, 40, GRAY);
    }
}


int main() {
    ClearTroops();
    CreateMapBonds();
    InitWindow(screenWidth, screenHeight, "Nameless Strategy Game");
    
    Image image = LoadImage("resources/map.png"); 
    Texture2D texture = LoadTextureFromImage(image);

    SetTargetFPS(60);
     
    while(!WindowShouldClose()) {
        MouseClicked = IsMouseButtonPressed(0);
        if(MouseClicked) { // Mouse Controls
            if(GameStarted) {
                GetMouseCoords();
            }
            if(GameStarted == false) {
                GameStarted = true;
            }
            cout << PixelX << " " << PixelY << endl;
        }
        BeginDrawing();
            ClearBackground(RAYWHITE);
            if(GameStarted) { // Game Started
                DrawTexture(texture, MapBorderX, MapBorderY, WHITE);
                DrawActions(image, texture.width, texture.height);
                DrawTurn(texture.width, texture.height);
            }
            else { // Title screen
                DrawText("Click anywhere to start a game", 20, 200, 38, BLACK);
            }
        EndDrawing();
    }
    UnloadImage(image);
    UnloadTexture(texture);
    CloseWindow();
    return 0;
}