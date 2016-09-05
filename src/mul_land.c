#include "mul_land.h"
#include "mul_index.h"
#include <stdio.h>
#include <stdlib.h>

void unload_land_textures()
{
    for(int i = 0; i < 0x10000; i++)
    {
        if(land_textures[i].width > 0)
        {
            UnloadTexture(land_textures[i]);
        }
    }
}

Texture2D get_land_texture(int index)
{
    if(land_textures[index].width == 0)
        land_textures[index] = load_land_texture(index);
    return land_textures[index];
}

Texture2D load_land_texture(int index)
{
    Texture2D texture;
    struct MulIndexEntry index_entry = get_mul_index("tmp/artidx.mul", index);

    FILE *art_fp = fopen("tmp/art.mul", "r");
    fseek(art_fp, index_entry.lookup, SEEK_SET);

    int32_t flag;
    fread(&flag, sizeof(int32_t), 1, art_fp);

    uint8_t *pixels;

    if(flag > 0xFFFF || flag == 0)
    {
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
        
    }
    else
    {
        /*
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
        */
    }

    texture = LoadTextureEx(pixels, 44, 44, UNCOMPRESSED_R8G8B8A8);

    free(pixels);

    return texture;
}
