#include "fonts.h"
#include "../core/types.h"
#include "../core/text.h"
#include "../core/texture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_ascii_fonts()
{
    FILE *fp = fopen("tmp/fonts.mul", "r");

    for(int i=0; i < 10; i++)
    {
        uint8 header;
        fread(&header, sizeof(uint8), 1, fp);

        for(int j=0; j < 224; j++)
        {
            uint8 width, height, set_header;
            fread(&width, sizeof(uint8), 1, fp);
            fread(&height, sizeof(uint8), 1, fp);
            fread(&set_header, sizeof(uint8), 1, fp);

            uint8 *pixels;

            int pixels_size = width * height * sizeof(uint32);
            pixels = (uint8 *)malloc(pixels_size);
            memset(pixels, 0, pixels_size);

            for(int k=0; k < width * height; k++)
            {
                int offset = k * sizeof(uint32);
                uint16 color16;
                fread(&color16, sizeof(uint16), 1, fp);
                
                if(color16 == 0x0000)
                {
                    pixels[offset] = 0;
                    pixels[offset + 1] = 0;
                    pixels[offset + 2] = 0;
                    pixels[offset + 3] = 0;
                }
                else
                {
                    pixels[offset] = (uint8)(((color16 & 0x7C00) >> 10) << 3);
                    pixels[offset + 1] = (uint8)(((color16 & 0x3E0) >> 5) << 3);
                    pixels[offset + 2] = (uint8)((color16 & 0x1F) << 3);
                    pixels[offset + 3] = (uint8)255;
                }
            }

            ascii_fonts[i].characters[j] = load_texture(pixels, width, height);

            free(pixels);
        }
    }

    fclose(fp);
}
