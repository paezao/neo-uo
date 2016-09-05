#include "art.h"
#include "index.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InitLandTextures()
{
    memset(&textures, 0, sizeof(Texture2D) * 0x3FFF);
}

void UnloadLandTextures()
{
    for(int i = 0; i < 0x3FFF; i++)
    {
        if(textures[i].width > 0)
        {
            UnloadTexture(textures[i]);
        }
    }
}

Texture2D * GetLandTexture(int index)
{
    if(textures[index].width == 0)
        textures[index] = LoadLandTexture(index);
    return &textures[index];
}

static Texture2D LoadLandTexture(int index)
{
    Texture2D texture;
    struct IndexEntry index_entry = GetIndexEntry("tmp/artidx.mul", index);

    FILE *art_fp = fopen("tmp/art.mul", "r");
    fseek(art_fp, index_entry.lookup, SEEK_SET);

    int32_t flag;
    fread(&flag, sizeof(int32_t), 1, art_fp);

    uint8_t *pixels;

    pixels = (uint8_t *)malloc(7744); // 44x44 tiles x 32bits

    for(int i = 0; i < 7744; i++)
    {
        pixels[i] = (uint8_t)0;
    }

    int x = 22;
    int y = 0;
    int line_width = 0;
    int pitch = 176;

    for(int i = 0; i < 22; i++)
    {
        x--;
        line_width += 2;
        for(int j = 0; j < line_width; j++)
        {
            int offset = (y * pitch) + (x * 4) + (j * 4);
            uint16_t color16;
            fread(&color16, sizeof(uint16_t), 1, art_fp);

            pixels[offset] = (uint8_t)(((color16 & 0x7C00) >> 10) << 3);
            pixels[offset + 1] = (uint8_t)(((color16 & 0x3E0) >> 5) << 3);
            pixels[offset + 2] = (uint8_t)((color16 & 0x1F) << 3);
            pixels[offset + 3] = (uint8_t)255;
        }
        y++;
    }

    for(int i = 0; i < 22; i++)
    {
        for(int j = 0; j < line_width; j++)
        {
            int read_offset = (y * pitch) + (x * 4) + (j * 4);
            uint16_t color16;
            fread(&color16, sizeof(uint16_t), 1, art_fp);

            pixels[read_offset] = (uint8_t)(((color16 & 0x7C00) >> 10) << 3);
            pixels[read_offset + 1] = (uint8_t)(((color16 & 0x3E0) >> 5) << 3);
            pixels[read_offset + 2] = (uint8_t)((color16 & 0x1F) << 3);
            pixels[read_offset + 3] = (uint8_t)255;
        }
        x++;
        y++;
        line_width -= 2;
    }

    texture = LoadTextureEx(pixels, 44, 44, UNCOMPRESSED_R8G8B8A8);

    fclose(art_fp);

    free(pixels);

    return texture;
}
