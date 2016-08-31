#include "mul_index.h"
#include <stdio.h>
#include <stdlib.h>

struct MulIndexEntry mul_index_entry(const char *path, int entry_id)
{
    struct MulIndexEntry index;

    FILE *fp = fopen(path, "r");

    fseek(fp, entry_id * 12, SEEK_SET);
    fread(&index.lookup, sizeof(int32_t), 1, fp);
    fread(&index.length, sizeof(int32_t), 1, fp);
    fread(&index.extra, sizeof(int32_t), 1, fp);

    fclose(fp);

    return index;
}

struct MulTexMap mul_tex_map(const char *path, struct MulIndexEntry index)
{
    struct MulTexMap tex_map;

    FILE *fp = fopen(path, "r");

    fseek(fp, index.lookup, SEEK_SET);

    if(index.length == 8192) 
    {
        tex_map.width = tex_map.height = 64;
    }
    else
    {
        tex_map.width = tex_map.height = 128;
    }

    uint16_t *buffer = (uint16_t *)malloc(index.length);
    tex_map.data = (uint8_t *)malloc(index.length * 2);

    fread(buffer, index.length, 1, fp);

    for(int i=0; i < tex_map.width * tex_map.height; i++)
    {
        int offset = i * 4;
        uint16_t color16 = buffer[i];

        tex_map.data[offset] = (uint8_t)(((color16 & 0x7C00) >> 10) << 3);
        tex_map.data[offset + 1] = (uint8_t)(((color16 & 0x3E0) >> 5) << 3);
        tex_map.data[offset + 2] = (uint8_t)((color16 & 0x1F) << 3);
        tex_map.data[offset + 3] = (uint8_t)255;
    }

    free(buffer);

    fclose(fp);

    return tex_map;
}
