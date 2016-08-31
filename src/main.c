#include "raylib.h"
#include "mul_index.h"

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Open UO");

    SetTargetFPS(60);

    struct MulIndexEntry index = mul_index_entry("tmp/texidx.mul", 2700);
    struct MulTexMap tex_map = mul_tex_map("tmp/texmaps.mul", index);

    Texture2D texture = LoadTextureEx(tex_map.data, 
            tex_map.width, 
            tex_map.height,
            UNCOMPRESSED_R8G8B8A8);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
