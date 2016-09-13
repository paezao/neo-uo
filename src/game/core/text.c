#include "text.h"
#include "texture.h"
#include "types.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

void draw_text(int x, int y, int font, const char *text, struct color color)
{
    int len = strlen(text);

    int last_x = x;
    int last_width = 0;
    for(int i=0; i < len; i++)
    {
        uint8 char_nr = text[i];
        struct texture *tex = ascii_fonts[font].characters[char_nr - 32];
        struct rectangle rect = {last_x + last_width, y, tex->width, tex->height};

        last_x += last_width;
        last_width = tex->width;

        draw_texture(rect, tex, color);
    }
}

const char * format_text(const char *text, ...)
{
    static char buffer[64];

    va_list args;
    va_start(args, text);
    vsprintf(buffer, text, args);
    va_end(args);

    return buffer;
}
