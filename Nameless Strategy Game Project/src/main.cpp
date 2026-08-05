#include <raylib.h>
#include <bits/stdc++.h>

int main() {
    int MouseX = 0;
    int MouseY = 0;
    int TileSelected = 0;
    Color MouseColor = {255, 0, 0, 0};

    const int screenWidth = 650;
    const int screenHeight = 300;

    int MapBorderX = 150;
    int MapBorderY = 0;

    InitWindow(screenWidth, screenHeight, "Nameless Strategy Game");
    
    Image image = LoadImage("resources/map.png"); 
    Texture2D texture = LoadTextureFromImage(image);

    SetTargetFPS(60);
     
    while(!WindowShouldClose()) {
        bool MouseClicked = IsMouseButtonDown(0);
        MouseX = GetMouseX();
        MouseY = GetMouseY();

        if(MouseClicked) {
            if(MouseX >= MapBorderX && MouseX <= MapBorderX + texture.width && MouseY >= MapBorderY && MouseY <= MapBorderY + texture.height) {
                int PixelX = MouseX - MapBorderX;
                int PixelY = MouseY - MapBorderY;

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
            else {
                TileSelected = 0;
            }
        }
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(texture, MapBorderX, MapBorderY, WHITE);
            switch(TileSelected) {
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
        EndDrawing();
    }
    UnloadImage(image);
    UnloadTexture(texture);
    CloseWindow();
    return 0;
}