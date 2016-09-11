#include "art.h"
#include "index.h"
#include "../core/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct texture * load_land_texture(int index)
{
    struct index_entry index_entry = get_index_entry("tmp/artidx.mul", index);

    FILE *art_fp = fopen("tmp/art.mul", "r");
    fseek(art_fp, index_entry.lookup, SEEK_SET);

    uint8 *pixels;

    pixels = (uint8 *)malloc(7744); // 44x44 tiles x 32bits
    memset(pixels, 0, 7744);

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
            uint16 color16;
            fread(&color16, sizeof(uint16), 1, art_fp);

            pixels[offset] = (uint8)(((color16 & 0x7C00) >> 10) << 3);
            pixels[offset + 1] = (uint8)(((color16 & 0x3E0) >> 5) << 3);
            pixels[offset + 2] = (uint8)((color16 & 0x1F) << 3);
            pixels[offset + 3] = (uint8)255;
        }
        y++;
    }

    for(int i = 0; i < 22; i++)
    {
        for(int j = 0; j < line_width; j++)
        {
            int read_offset = (y * pitch) + (x * 4) + (j * 4);
            uint16 color16;
            fread(&color16, sizeof(uint16), 1, art_fp);

            pixels[read_offset] = (uint8)(((color16 & 0x7C00) >> 10) << 3);
            pixels[read_offset + 1] = (uint8)(((color16 & 0x3E0) >> 5) << 3);
            pixels[read_offset + 2] = (uint8)((color16 & 0x1F) << 3);
            pixels[read_offset + 3] = (uint8)255;
        }
        x++;
        y++;
        line_width -= 2;
    }

    struct texture *texture = load_texture(pixels, 44, 44);

    fclose(art_fp);

    free(pixels);

    return texture;
}

struct texture * get_land_texture(int index)
{
    if(!land_textures[index])
        land_textures[index] = load_land_texture(index);
    return land_textures[index];
}

void unload_land_textures()
{
    for(int i=0; i < 0x3FFF; i++)
    {
        if(land_textures[i])
            unload_texture(land_textures[i]);
    }
}

static struct texture * load_static_texture(int index)
{
    index += 0x4000;
    struct index_entry index_entry = get_index_entry("tmp/artidx.mul", index);

    FILE *art_fp = fopen("tmp/art.mul", "r");
    fseek(art_fp, index_entry.lookup, SEEK_SET);

    int32 header;
    fread(&header, sizeof(int32), 1, art_fp);

    uint16 width, height;
    fread(&width, sizeof(uint16), 1, art_fp);
    fread(&height, sizeof(uint16), 1, art_fp);

    uint16 *lookup_table = (uint16 *)malloc(sizeof(uint16) * height);
    fread(lookup_table, sizeof(uint16), height, art_fp);

    int pixels_size = width * height * sizeof(uint32);
    uint8 *pixels = (uint8 *)malloc(pixels_size);
    memset(pixels, 0, pixels_size);

    int data_start = ftell(art_fp);
    uint16 x = 0;
    int y = 0;

    fseek(art_fp, data_start + lookup_table[y] * 2, SEEK_SET);
    while(y < height)
    {
        uint16 offset, run;
        fread(&offset, sizeof(uint16), 1, art_fp);
        fread(&run, sizeof(uint16), 1, art_fp);

        if(offset == 0 && run == 0)
        {
            x = 0;
            y++;
            fseek(art_fp, data_start + lookup_table[y] * 2, SEEK_SET);
        }
        else
        {
            x += offset;
            for(int i=0; i < run; i++)
            {
                uint16 pixel_offset = (y * width * 4) + (x * 4);
                uint16 color16;
                fread(&color16, sizeof(uint16), 1, art_fp);

                pixels[pixel_offset] = (uint8)(((color16 & 0x7C00) >> 10) << 3);
                pixels[pixel_offset + 1] = (uint8)(((color16 & 0x3E0) >> 5) << 3);
                pixels[pixel_offset + 2] = (uint8)((color16 & 0x1F) << 3);
                pixels[pixel_offset + 3] = (uint8)255;

                x += 1;
            }
        }
    }

    struct texture *texture = load_texture(pixels, width, height);

    fclose(art_fp);

    free(pixels);
    free(lookup_table);

    return texture;
}

struct texture * get_static_texture(int index)
{
    if(!static_textures[index])
        static_textures[index] = load_static_texture(index);
    return static_textures[index];
}

void unload_static_textures()
{
    for(int i=0; i < 0x3FFF; i++)
    {
        if(static_textures[i])
            unload_texture(static_textures[i]);
    }
}
