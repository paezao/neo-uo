#include "ground_tiles.h"
#include "mul_index.h"
#include <stdio.h>
#include <stdlib.h>

struct GroundTile * LoadGroundTiles()
{
    struct GroundTile *ground_tiles;

    FILE *texidx_file = fopen("tmp/texidx.mul", "r");
    FILE *texmaps_file = fopen("tmp/texmaps.mul", "r");

    fseek(texidx_file, 0, SEEK_END); // seek to end of file
    int index_file_size = ftell(texidx_file); // get current file pointer
    fseek(texidx_file, 0, SEEK_SET); // seek back to beginning of file

    int nr_of_entries = index_file_size / sizeof(struct MulIndexEntry);

    ground_tiles = (struct GroundTile *)malloc(nr_of_entries * sizeof(struct GroundTile));

    for(int i=0; i < nr_of_entries; i++)
    {
        struct MulIndexEntry index;
        fread(&index.lookup, sizeof(int32_t), 1, texidx_file);
        fread(&index.length, sizeof(int32_t), 1, texidx_file);
        fread(&index.extra, sizeof(int32_t), 1, texidx_file);

        if(index.lookup == -1 || index.length == -1)
        {
            continue;
        }

        struct MulTexMap tex_map;
        uint16_t *buffer = (uint16_t *)malloc(index.length);
        tex_map.data = (uint8_t *)malloc(index.length * 2);

        fseek(texmaps_file, index.lookup, SEEK_SET);
        fread(buffer, index.length, 1, texmaps_file);
        
        if(index.length == 8192) 
        {
            tex_map.width = tex_map.height = 64;
        }
        else
        {
            tex_map.width = tex_map.height = 128;
        }

        for(int j=0; j < tex_map.width * tex_map.height; j++)
        {
            int offset = j * 4;
            uint16_t color16 = buffer[j];

            tex_map.data[offset] = (uint8_t)(((color16 & 0x7C00) >> 10) << 3);
            tex_map.data[offset + 1] = (uint8_t)(((color16 & 0x3E0) >> 5) << 3);
            tex_map.data[offset + 2] = (uint8_t)((color16 & 0x1F) << 3);
            tex_map.data[offset + 3] = (uint8_t)255;
        }

        //free(buffer);

        Texture2D texture = LoadTextureEx(tex_map.data, 
                tex_map.width, 
                tex_map.height,
                UNCOMPRESSED_R8G8B8A8);

        char key_string[10];
        sprintf(key_string, "%d", i);

        struct GroundTile ground_tile;
        ground_tile.id = i;
        ground_tile.texture = texture;
        ground_tiles[i] = ground_tile;
    }

    fclose(texidx_file);
    fclose(texmaps_file);

    return ground_tiles;
}
