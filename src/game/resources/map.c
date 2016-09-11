#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"

Map * load_map()
{
    Map *map = (Map *)malloc(sizeof(Map));    

    int width_in_blocks = 896;
    int height_in_blocks = 512;
    int tile_x_offset = 0;
    int tile_y_offset = 0;
    
    FILE *fp = fopen("tmp/map0.mul", "r");
    FILE *st_fp = fopen("tmp/statics0.mul", "r");
    for(int block_x = 0; block_x < width_in_blocks; block_x++)
    {
        tile_x_offset = block_x * 8;
        tile_y_offset = 0;

        for(int block_y = 0; block_y < height_in_blocks; block_y++)
        {
            tile_y_offset = block_y * 8;

            // Read Tile
            int32 header;
            fread(&header, sizeof(int32), 1, fp); // Read Header

            for(int y = 0; y < 8; y++)
            {
                for(int x = 0; x < 8; x++)
                {
                    Tile tile;
                    vector_init(&tile.statics);
                    fread(&tile.texture_id, sizeof(uint16), 1, fp);
                    fread(&tile.z, sizeof(int8), 1, fp);
                    map->tiles[tile_x_offset + x][tile_y_offset + y] = tile;
                }
            }

            // Read Statics
            int index = (block_x * height_in_blocks) + block_y;
            IndexEntry index_entry = get_index_entry("tmp/staidx0.mul", index);
            
            if(index_entry.lookup == 0xFFFFFFFF)
                continue;

            fseek(st_fp, index_entry.lookup, SEEK_SET);

            uint8 x_offset, y_offset = 0;
            uint16 unknown = 0;

            for(int i = 0; i < index_entry.length / 7; i++)
            {
                Static *static_ = malloc(sizeof(Static));
                memset(static_, 0, sizeof(Static));
                fread(&static_->texture_id, sizeof(uint16), 1, st_fp);
                fread(&x_offset, sizeof(uint8), 1, st_fp);
                fread(&y_offset, sizeof(uint8), 1, st_fp);
                fread(&static_->z, sizeof(int8), 1, st_fp);
                fread(&unknown, sizeof(uint16), 1, st_fp);

                int statics_x_offset = tile_x_offset + x_offset;
                int statics_y_offset = tile_y_offset + y_offset;

                vector_add(&map->tiles[statics_x_offset][statics_y_offset].statics, static_);
            }

            // Sort Statics
            for(int y = 0; y < 8; y++)
            {
                for(int x = 0; x < 8; x++)
                {
                    Tile *tile = &map->tiles[tile_x_offset + x][tile_y_offset + y];

                    int n = vector_total(&tile->statics);

                    for (int c = 0 ; c < ( n - 1 ); c++)
                    {
                        for (int d = 0 ; d < n - c - 1; d++)
                        {
                            Static *_static_1 = vector_get(&tile->statics, d);
                            Static *_static_2 = vector_get(&tile->statics, d + 1);
                            if (_static_1->z > _static_2->z)
                            {
                                vector_set(&tile->statics, d, _static_2);
                                vector_set(&tile->statics, d + 1, _static_1);
                            }
                        }
                    }
                }
            }
        }
    }
    fclose(fp);
    fclose(st_fp);

    return map;
}

void unload_map(Map *map)
{
}
