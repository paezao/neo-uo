#include "text.h"
#include "texture.h"
#include "types.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

void draw_text(int x, int y, int font, char *text, struct color color)
{
    int len = strlen(text);

    int last_x = x;
    int last_width = 0;
    for(int i=0; i < len; i++)
    {
        uint8 char_nr = text[i];
        struct texture *tex = ascii_fonts[font].characters[char_nr - 32];

        int current_x = last_x + last_width;

        struct vector3 vertices[4] = {
            {current_x, y, -1.0f},
            {current_x, y + tex->height, -1.0f},
            {current_x + tex->width, y + tex->height, -1.0f},
            {current_x + tex->width, y, -1.0f}
        };

        draw_texture_adv(vertices, tex, color);

        last_x += last_width;
        last_width = tex->width;
    }
}

struct size get_text_size(int font, const char *text)
{
    int len = strlen(text);

    struct size text_size = {0};

    for(int i=0; i < len; i++)
    {
        uint8 char_nr = text[i];
        struct texture *tex = ascii_fonts[font].characters[char_nr - 32];
        text_size.width += tex->width;

        if(text_size.height < tex->height) text_size.height = tex->height;
    }

    return text_size;
}

char * format_text(char *text, ...)
{
    static char buffer[64];

    va_list args;
    va_start(args, text);
    vsprintf(buffer, text, args);
    va_end(args);

    return buffer;
}
