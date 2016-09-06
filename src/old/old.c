
/*
void render_map_block(struct MulMapBlock block, int offset_x, int offset_y)
{
    //struct MulMapBlock block = map->blocks[block_nr];

    int tile_size = 44;
    int half_tile = tile_size / 2;
    
    int initial_tiling_offset_x = offset_x - 3 * tile_size;
    int initial_tiling_offset_y = offset_y;

    int tiling_offset_x = offset_x;
    int tiling_offset_y = offset_y;

    for(int y = 0; y < 8; y++)
    {
        tiling_offset_x = initial_tiling_offset_x + y * half_tile;
        tiling_offset_y = initial_tiling_offset_y + y * half_tile;

        for(int x = 0; x < 8; x++)
        {
            int position_x = x * half_tile;
            int position_y = y * half_tile;

            int iso_x = tiling_offset_x + x * half_tile;
            int iso_y = tiling_offset_y - position_x;

            int offset = x * y;

            // Z
            //iso_y += block.cells[offset].z;

            Texture2D texture = get_land_texture(block.cells[offset].tile_id);
            Rectangle sourceRec = {0, 0, texture.width, texture.height};
            Rectangle destRec = {iso_x, iso_y, tile_size, tile_size};

            if(texture.width > 0 && texture.height > 0)
            {
                DrawLand(texture,
                        sourceRec,
                        destRec,
                        WHITE);
            }

            // Debug Circle
            //DrawCircleLines(destRec.x, destRec.y, 1.0f, RED);
        }
    }
}
*/

/*
int main()
{
    int screenWidth = 800;
    int screenHeight = 450;

    // 19 tiles wide / 11 tiles down
    // 3 blocks wide / <F6>`

    int player_location_x = 1323;
    int player_location_y = 1624;

    InitWindow(screenWidth, screenHeight, "Neo UO");

    SetTargetFPS(60);

    //map = LoadMap0();

    int half_screen_width = GetScreenWidth() / 2;
    int half_screen_height = GetScreenHeight() / 2;

    //Texture2D tile = get_land_texture(3);
    int player_block_x = player_location_x / 8;
    int player_block_y = player_location_y / 8;

    int initial_block_load_x = player_block_x;
    int initial_block_load_y = player_block_y;

    struct MulMapBlock blocks[5][5];
    for(int x = 0; x < 5; x++)
    {
        for(int y = 0; y < 5; y++)
        {
            blocks[x][y] = LoadMapBlock(initial_block_load_x, initial_block_load_y);
        }
    }
    
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

        
        //Rectangle sourceRec = {0, 0, tile.width, tile.height};
        //Rectangle destRec = {GetScreenWidth() / 2, GetScreenHeight() / 2, tile.width, tile.height};

        //DrawLand(tile,
//                sourceRec,
 //               destRec,
  //              WHITE);

        // Top
        //render_map_block(player_block_x, player_block_y - 1, half_screen_width + 44 * 4 * 1, half_screen_height - 44 * 4 * 1);
        //render_map_block(player_block_x - 1, player_block_y - 1, half_screen_width, half_screen_height - 44 * 4 * 2);
        //render_map_block(player_block_x + 1, player_block_y - 1, half_screen_width + 44 * 4 * 2, half_screen_height);
        
        // Middle
        render_map_block(blocks[0][0], half_screen_width, half_screen_height);
        //render_map_block(player_block_x - 1, player_block_y, half_screen_width - 44 * 4 * 1, half_screen_height - 44 * 4 * 1);
        //render_map_block(player_block_x - 2, player_block_y, half_screen_width - 44 * 4 * 2, half_screen_height - 44 * 4 * 2);
        //render_map_block(player_block_x + 1, player_block_y, half_screen_width + 44 * 4 * 1, half_screen_height + 44 * 4 * 1);
        //render_map_block(player_block_x + 2, player_block_y, half_screen_width + 44 * 4 * 2, half_screen_height + 44 * 4 * 2);

        // Bottom
        //render_map_block(player_block_x, player_block_y + 1, half_screen_width - 44 * 4 * 1, half_screen_height + 44 * 4 * 1);
        //render_map_block(player_block_x - 1, player_block_y + 1, half_screen_width - 44 * 4 * 2, half_screen_height);
        //render_map_block(player_block_x - 2, player_block_y + 1, half_screen_width - 44 * 4 * 3, half_screen_height - 44 * 4 * 1);
        //render_map_block(player_block_x + 1, player_block_y + 1, half_screen_width, half_screen_height + 44 * 4 * 2);

        End3dMode();

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
*/
