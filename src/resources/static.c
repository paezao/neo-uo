#include "static.h"
#include "index.h"
#include <stdio.h>
#include <stdlib.h>

void UnloadStaticTextures()
{
    for(int i = 0; i < 0x10000; i++)
    {
        if(textures[i].width > 0)
        {
            UnloadTexture(textures[i]);
        }
    }
}

Texture2D GetStaticTexture(int index)
{
    if(textures[index].width == 0)
        textures[index] = LoadStaticTexture(index);
    return textures[index];
}

static Texture2D LoadStaticTexture(int index)
{
    Texture2D texture;
    struct IndexEntry index_entry = GetIndexEntry("tmp/artidx.mul", index);

    FILE *art_fp = fopen("tmp/art.mul", "r");
    fseek(art_fp, index_entry.lookup, SEEK_SET);

    int32_t flag;
    fread(&flag, sizeof(int32_t), 1, art_fp);

    uint8_t *pixels;

    if(flag > 0xFFFF || flag == 0)
    {
        return texture;
    }
    else
    {
        int32_t width, height;
        fread(&width, sizeof(int32_t), 1, art_fp);
        fread(&height, sizeof(int32_t), 1, art_fp);

        if (width <= 0 || height <= 0)
        {
            return texture;
        }

        uint16_t *lookups = (uint16_t *)malloc(height * sizeof(uint16_t));
        pixels = (uint8_t *)malloc(width * height * sizeof(uint32_t));

        fread(&lookups, sizeof(int16_t), height, art_fp);
        fseek(art_fp, height * 2, SEEK_CUR);

        int data_start = ftell(art_fp);
        int x, y = 0;

        fseek(art_fp, data_start + lookups[y] * 2, SEEK_SET);
        for(int y = 0; y < height; y++)
        {
            uint16_t xoffs, run;
            fread(&xoffs, sizeof(uint16_t), 1, art_fp);
            fread(&run, sizeof(uint16_t), 1, art_fp);

            if(xoffs + run >= 2048)
            {
                break;
            }
            else if(xoffs + run != 0)
            {
                x += xoffs;
                for(int j = 0; j < run; j++)
                {
                    int read_offset = y * width + j * 4;
                    uint16_t color16;
                    fread(&color16, sizeof(uint16_t), 1, art_fp);

                    pixels[read_offset] = (uint8_t)(((color16 & 0x7C00) >> 10) << 3);
                    pixels[read_offset + 1] = (uint8_t)(((color16 & 0x3E0) >> 5) << 3);
                    pixels[read_offset + 2] = (uint8_t)((color16 & 0x1F) << 3);
                    pixels[read_offset + 3] = (uint8_t)255;
                }
                x += run;
            }
            else
            {
                x = 0;
                y++;
                fseek(art_fp, data_start + lookups[y] * 2, SEEK_SET);
            }
        }

        free(lookups);
    }

    texture = LoadTextureEx(pixels, 44, 44, UNCOMPRESSED_R8G8B8A8);

    free(pixels);

    return texture;
}
