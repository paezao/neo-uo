#include "maps.h"
#include <stdio.h>
#include <stdlib.h>

struct Map0 * LoadMap0()
{
    struct Map0 *map = (struct Map0 *)malloc(sizeof(struct Map0));

    FILE *fp = fopen("tmp/map0.mul", "r");

    for (int x = 0; x < 768; x++)
    {
        for (int y = 0; y < 512; y++)
        {
            struct MulMapBlock block;
            fread(&block.header, sizeof(int32_t), 1, fp); // Read Header

            for(int i = 0; i < 64; i++)
            {
                struct MulMapCell cell;
                fread(&cell.tile_id, sizeof(uint16_t), 1, fp);
                fread(&cell.z, sizeof(int8_t), 1, fp);
                block.cells[i] = cell;
            }

            map->blocks[x][y] = block;
        }
    }

    fclose(fp);

    return map;
}
