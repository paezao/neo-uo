#include "raylib.h"
#include "misc.h"
#include "resources/maps.h"
#include "resources/art.h"
#include <stdlib.h>

struct Map map;

int main()
{
    InitWindow(800, 450, "Neo UO");
    SetTargetFPS(60);

    LoadMap(&map);

    int player_location_x = 1323;
    int player_location_y = 1624;

    while(!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) { player_location_x += 1; player_location_y -= 1; }
        if (IsKeyDown(KEY_LEFT)) { player_location_x -= 1; player_location_y += 1; }
        if (IsKeyDown(KEY_UP)) { player_location_y -= 1; player_location_x -= 1; }
        if (IsKeyDown(KEY_DOWN)) { player_location_y += 1; player_location_x += 1; }

        BeginDrawing();

        ClearBackground(BLACK);
        BeginBlendMode(BLEND_ALPHA);

        Begin3dOrthoMode();
        DrawMap(&map, player_location_x, player_location_y, 12);
        End3dMode();

        DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadLandTextures();

    CloseWindow();

    return 0;
}
