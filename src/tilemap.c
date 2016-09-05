#include "tilemap.h"
#include "misc.h"
#include "mul_land.h"
#include <stdio.h>

void LoadTileMap(struct TileMap * tilemap)
{
    int width_in_blocks = 896;
    int height_in_blocks = 512;
    int nr_of_blocks = width_in_blocks * height_in_blocks;
    int tile_x_offset = 0;
    int tile_y_offset = 0;
    
    FILE *fp = fopen("tmp/map0.mul", "r");
    for(int block_x = 0; block_x < width_in_blocks; block_x++)
    {
        tile_x_offset = block_x * 8;
        tile_y_offset = 0;

        for(int block_y = 0; block_y < height_in_blocks; block_y++)
        {
            tile_y_offset = block_y * 8;

            int32_t header;
            fread(&header, sizeof(int32_t), 1, fp); // Read Header

            for(int y = 0; y < 8; y++)
            {
                for(int x = 0; x < 8; x++)
                {
                    struct Tile tile;
                    fread(&tile.texture_id, sizeof(uint16_t), 1, fp);
                    fread(&tile.z, sizeof(int8_t), 1, fp);
                    tilemap->tiles[tile_x_offset + x][tile_y_offset + y] = tile;
                }
            }
        }
    }
    fclose(fp);
}

void DrawTileMap(struct TileMap * tilemap, int x, int y, int radius)
{
    int init_x = x - radius;
    int init_y = y - radius;
    int end_x = x + radius;
    int end_y = y + radius;

    int anchor_x = GetScreenWidth() / 2;
    int anchor_y = GetScreenHeight() / 2 + 100;

    Texture2D texture;

    for(int y = init_y; y <= end_y; y++)
    {
        for(int x = init_x; x <= end_x; x++)
        {
            texture = get_land_texture(tilemap->tiles[x][y].texture_id);

            int plot_x = anchor_x + (((x - init_x) - (y - init_y)) * texture.width / 2);
            int plot_y = (((x - init_x) + (y - init_y)) * texture.height / 2) - anchor_y;

            Rectangle sourceRec = {0, 0, texture.width, texture.height};
            Rectangle destRec = {plot_x, 
                plot_y, 
                texture.width, 
                texture.height};

            DrawLand(texture,
                    sourceRec,
                    destRec,
                    WHITE);
        }
    }
}
