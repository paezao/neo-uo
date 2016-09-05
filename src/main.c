#include "raylib.h"
#include "tilemap.h"
#include "misc.h"
#include "mul_land.h"

struct TileMap tilemap;

int main()
{
    InitWindow(800, 450, "Neo UO");
    SetTargetFPS(60);

    LoadTileMap(&tilemap);

    int player_location_x = 1323;
    int player_location_y = 1624;

    while(!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) player_location_x += 1;
        if (IsKeyDown(KEY_LEFT)) player_location_x -= 1;
        if (IsKeyDown(KEY_UP)) player_location_y -= 1;
        if (IsKeyDown(KEY_DOWN)) player_location_y += 1;

        BeginDrawing();

        ClearBackground(BLACK);
        BeginBlendMode(BLEND_ALPHA);

        Begin3dOrthoMode();
        DrawTileMap(&tilemap, player_location_x, player_location_y, 12);
        End3dMode();

        DrawFPS(10, 10);

        EndDrawing();
    }

    return 0;
}
