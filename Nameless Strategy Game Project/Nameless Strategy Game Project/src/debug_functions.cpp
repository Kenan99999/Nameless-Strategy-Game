#include "functions.h"
#include "globals.h"
#include <bits/stdc++.h>
#include <raylib.h>

using namespace std;

void TileCenterSelector() {
    InitWindow(1920, 1080, "Click to tile centers");
    ToggleBorderlessWindowed();
    GameCamera.offset = {400,0};
    GameCamera.target = {400,0};
    GameCamera.rotation = 0.0f;
    GameCamera.zoom = 1.0f;
    Image Map_png = LoadImage("resources/map.png");
    Texture2D Map = LoadTextureFromImage(Map_png);
    vector<int> TileCenters;
    int red = 0;
    int blue = 0;
    int green = 0;
    int TempTile = 0;
    SetTargetFPS(60);
    while(!WindowShouldClose()) {
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
        MouseClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        /*if(IsKeyPressed(KEY_S)) {         Click to centers mode (use it only when needed)
            if(!exists("centers")) {
                create_directory("centers");
            }
            string file_addres = "centers/tiles.txt";
            ofstream File(file_addres);

            if(File.is_open()) {
                for(int i = 0; i < TileCenters.size(); ++i) {
                    File << TileCenters[i] << endl;
                }
            }
        }
        if(IsKeyPressed(KEY_ENTER)) {
            TileCenters.push_back(MouseX);
            TileCenters.push_back(MouseY);
        }*/
        /*if(IsKeyPressed(KEY_S)) {         Click to create bonds mode (use it only when needed)
            if(!exists("centers")) {
                create_directory("centers");
            }
            string file_addres = "centers/bonds.txt";
            ofstream File(file_addres);

            if(File.is_open()) {
                for(int i = 0; i < 47; ++i) {
                    File << Tiles[i].size() << endl;
                    File << i << endl;
                    for(auto j : Tiles[i]) {
                        File << j << endl;
                    }
                }
            }
        }
        if(IsKeyPressed(KEY_A)) {
            TempTile = TileSelected;
        }
        if(IsKeyPressed(KEY_C)) {
            Tiles[TempTile - 1].push_back(TileSelected - 1);
        }*/
        if(MouseClicked) {
            GetMouseCoords();
            if(MouseX >= MapBorderX && MouseX <= MapBorderX + Map.width && MouseY >= MapBorderY && MouseY <= MapBorderY + Map.height) {
                Vector2 MouseCoords = GetScreenToWorld2D(GetMousePosition(), GameCamera);
                MouseX = MouseCoords.x;
                MouseY = MouseCoords.y;
                MouseColor = GetImageColor(Map_png, MouseX - 400, MouseY);
                red = MouseColor.r;
                blue = MouseColor.b;
                green = MouseColor.g;
                if(red > 0) {
                    TileSelected = red / 10;
                }
                else if(blue > 0) {
                    TileSelected = blue / 10 + 38;
                }
                else if(green > 0)  {
                    TileSelected = green / 10 + 25;
                }
            }
        }
        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode2D(GameCamera);
        DrawTextureEx(Map, {400,0}, 0.0f, 1.0f, WHITE);
        EndMode2D();
        DrawRectangle(0, 0, 400, 1080, WHITE);
        DrawText(TextFormat("Tile: %d\nMouseX: %d\nMouseY: %d", TileSelected, MouseX, MouseY), 10, 10, 30, BLACK);
        EndDrawing();
    }
    UnloadImage(Map_png);
    UnloadTexture(Map);
    CloseWindow();
    exit(0);
}