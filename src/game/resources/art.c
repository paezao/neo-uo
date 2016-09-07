#include "art.h"
#include "index.h"
#include "../core/types.h"
#include <stdio.h>
#include <stdlib.h>

Texture * load_land_texture(int index)
{
    IndexEntry index_entry = get_index_entry("tmp/artidx.mul", index);

    FILE *art_fp = fopen("tmp/art.mul", "r");
    fseek(art_fp, index_entry.lookup, SEEK_SET);

    int32 flag;
    fread(&flag, sizeof(int32), 1, art_fp);

    uint8 *pixels;

    pixels = (uint8 *)malloc(7744); // 44x44 tiles x 32bits

    for(int i = 0; i < 7744; i++)
    {
        pixels[i] = (uint8)0;
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

    Texture *texture = load_texture(pixels, 44, 44);

    fclose(art_fp);

    free(pixels);

    return texture;
}
