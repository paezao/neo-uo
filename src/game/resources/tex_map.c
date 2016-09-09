#include "tex_map.h"
#include "index.h"
#include "../core/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Texture * load_tex_map_texture(int index)
{
    IndexEntry index_entry = get_index_entry("tmp/texidx.mul", index);

    FILE *art_fp = fopen("tmp/texmaps.mul", "r");
    fseek(art_fp, index_entry.lookup, SEEK_SET);

    uint8 *pixels;

    int width = 64, height = 64;
    if(index_entry.length == 0x8000) {
        width = 128, height = 128;
    }

    int pixels_size = width * height * sizeof(uint32);
    pixels = (uint8 *)malloc(pixels_size);
    memset(pixels, 0, pixels_size);

    for(int i=0; i < width * height; i++)
    {
        int offset = i * sizeof(uint32);
        uint16 color16;
        fread(&color16, sizeof(uint16), 1, art_fp);

        pixels[offset] = (uint8)(((color16 & 0x7C00) >> 10) << 3);
        pixels[offset + 1] = (uint8)(((color16 & 0x3E0) >> 5) << 3);
        pixels[offset + 2] = (uint8)((color16 & 0x1F) << 3);
        pixels[offset + 3] = (uint8)255;
    }

    Texture *texture = load_texture(pixels, width, height);

    fclose(art_fp);

    free(pixels);

    return texture;
}

Texture * get_tex_map_texture(int index)
{
    if(!tex_map_textures[index])
        tex_map_textures[index] = load_tex_map_texture(index);
    return tex_map_textures[index];
}

void unload_tex_map_textures()
{
    for(int i=0; i < 0x3FFF; i++)
    {
        if(tex_map_textures[i])
            unload_texture(tex_map_textures[i]);
    }
}
