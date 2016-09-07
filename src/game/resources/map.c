#include "map.h"
#include <stdio.h>
#include <stdlib.h>

Map * load_map()
{
    Map *map = (Map *)malloc(sizeof(Map));    

    int width_in_blocks = 896;
    int height_in_blocks = 512;
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
                    map->tiles[tile_x_offset + x][tile_y_offset + y] = tile;
                }
            }
        }
    }
    fclose(fp);

    return map;
}
