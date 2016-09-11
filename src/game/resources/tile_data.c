#include "tile_data.h"
#include "index.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_tile_data()
{
    FILE *fp = fopen("tmp/tiledata.mul", "r");

    for(int i=0; i < 0x4000; ++i)
    {
        if (i == 1 || (i > 0 && (i & 0x1F) == 0))
        {
            int32 header;
            fread(&header, sizeof(int32), 1, fp);
        }

        fread(&land_tile_data[i].flags, sizeof(uint32), 1, fp);
        fread(&land_tile_data[i].texture_id, sizeof(uint16), 1, fp);
        fread(&land_tile_data[i].name, sizeof(char) * 20, 1, fp);
    }

    for(int i=0; i < 0x4000; ++i)
    {
        if((i & 0x1F) == 0)
        {
            int32 header;
            fread(&header, sizeof(int32), 1, fp);
        }

        fread(&static_tile_data[i].flags, sizeof(uint32), 1, fp);
        fread(&static_tile_data[i].weight, sizeof(uint8), 1, fp);
        fread(&static_tile_data[i].quality, sizeof(uint8), 1, fp);
        fread(&static_tile_data[i].unknown1, sizeof(int16), 1, fp);
        fread(&static_tile_data[i].unknown2, sizeof(uint8), 1, fp);
        fread(&static_tile_data[i].quantity, sizeof(uint8), 1, fp);
        fread(&static_tile_data[i].animation, sizeof(int16), 1, fp);
        fread(&static_tile_data[i].unknown3, sizeof(uint8), 1, fp);
        fread(&static_tile_data[i].hue, sizeof(uint8), 1, fp);
        fread(&static_tile_data[i].unknown4, sizeof(uint8), 1, fp);
        fread(&static_tile_data[i].unknown5, sizeof(uint8), 1, fp);
        fread(&static_tile_data[i].height, sizeof(uint8), 1, fp);
        fread(&static_tile_data[i].name, sizeof(char) * 20, 1, fp);
    }

    fclose(fp);
}

LandTileData * get_land_tile_data(int index)
{
    return &land_tile_data[index];
}

StaticTileData * get_static_tile_data(int index)
{
    return &static_tile_data[index];
}
