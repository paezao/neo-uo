#include "raylib.h"
#include "mul_index.h"
#include "misc.h"
#include "ground_tiles.h"
#include "maps.h"

struct GroundTile *ground_tiles;
struct Map0 *map;

void render_map_block(int x, int y, int offset_x, int offset_y)
{
    struct MulMapBlock block = map->blocks[x][y];

    int tile_size = 44;
    int half_tile = tile_size / 2;

    int initial_tiling_offset_x = offset_x;
    int initial_tiling_offset_y = offset_y - 3 * tile_size;

    int tiling_offset_x = offset_x;
    int tiling_offset_y = offset_y;

    for(int x = 0; x < 8; x++)
    {
        tiling_offset_x = initial_tiling_offset_x + x * half_tile;
        tiling_offset_y = initial_tiling_offset_y + x * half_tile;

        for(int y = 0; y < 8; y++)
        {
            int position_x = x * half_tile;
            int position_y = y * half_tile;

            int iso_x = tiling_offset_x - position_y;
            int iso_y = tiling_offset_y + y * half_tile;

            int offset = x * y;

            // Z
            //iso_y += block.cells[offset].z;

            struct GroundTile ground_tile = ground_tiles[block.cells[offset].tile_id];
            Rectangle sourceRec = {0, 0, ground_tile.texture.width, ground_tile.texture.height};
            Rectangle destRec = {iso_x, iso_y, tile_size, tile_size};

            DrawGroundTile(ground_tile.texture, 
                    sourceRec,
                    destRec,
                    WHITE);

            // Debug Circle
            //DrawCircleLines(destRec.x, destRec.y, 1.0f, RED);
        }
    }
}

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;

    int player_location_x = 1323;
    int player_location_y = 1624;

    InitWindow(screenWidth, screenHeight, "Neo UO");

    SetTargetFPS(60);

    ground_tiles = LoadGroundTiles();
    map = LoadMap0();

    int half_screen_width = GetScreenWidth() / 2;
    int half_screen_height = GetScreenHeight() / 2;

    while(!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) player_location_x += 1;
        if (IsKeyDown(KEY_LEFT)) player_location_x -= 1;
        if (IsKeyDown(KEY_UP)) player_location_y -= 1;
        if (IsKeyDown(KEY_DOWN)) player_location_y += 1;

        ClearBackground(BLACK);

        Begin3dOrthoMode();

        int player_block_x = player_location_x / 8;
        int player_block_y = player_location_y / 8;
        
        // Middle
        render_map_block(player_block_x, player_block_y, half_screen_width, half_screen_height);
        render_map_block(player_block_x - 1, player_block_y, half_screen_width - 44 * 4 * 1, half_screen_height - 44 * 4 * 1);
        render_map_block(player_block_x - 2, player_block_y, half_screen_width - 44 * 4 * 2, half_screen_height - 44 * 4 * 2);
        render_map_block(player_block_x + 1, player_block_y, half_screen_width + 44 * 4 * 1, half_screen_height + 44 * 4 * 1);
        render_map_block(player_block_x + 2, player_block_y, half_screen_width + 44 * 4 * 2, half_screen_height + 44 * 4 * 2);

        // Bottom
        render_map_block(player_block_x, player_block_y + 1, half_screen_width - 44 * 4 * 1, half_screen_height + 44 * 4 * 1);
        render_map_block(player_block_x - 1, player_block_y + 1, half_screen_width - 44 * 4 * 2, half_screen_height);
        render_map_block(player_block_x - 2, player_block_y + 1, half_screen_width - 44 * 4 * 3, half_screen_height - 44 * 4 * 1);

        End3dMode();

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
