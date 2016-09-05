#include "maps.h"
#include <stdio.h>
#include <stdlib.h>

struct Map0 * LoadMap0()
{
    struct Map0 *map = (struct Map0 *)malloc(sizeof(struct Map0));

    FILE *fp = fopen("tmp/map0.mul", "r");

    int nr_of_blocks = 896 * 512;

    for (int i = 0; i < nr_of_blocks; i++)
    {
        struct MulMapBlock block;
        fread(&block.header, sizeof(int32_t), 1, fp); // Read Header

        for(int j = 0; j < 64; j++)
        {
            struct MulMapCell cell;
            fread(&cell.tile_id, sizeof(uint16_t), 1, fp);
            fread(&cell.z, sizeof(int8_t), 1, fp);
            block.cells[j] = cell;
        }

        map->blocks[i] = block;
    }

    fclose(fp);

    return map;
}

struct MulMapBlock LoadMapBlock(int x, int y)
{
    struct MulMapBlock block;

    int block_nr = (x * 512) + y;
    int nr_of_blocks = 896 * 512;

    FILE *fp = fopen("tmp/map0.mul", "r");
    fseek(fp, block_nr * 196, SEEK_SET);

    fread(&block.header, sizeof(int32_t), 1, fp); // Read Header

    for(int j = 0; j < 64; j++)
    {
        struct MulMapCell cell;
        fread(&cell.tile_id, sizeof(uint16_t), 1, fp);
        fread(&cell.z, sizeof(int8_t), 1, fp);
        block.cells[j] = cell;
    }

    fclose(fp);

    return block;
}
