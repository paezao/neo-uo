#include "text.h"
#include "texture.h"
#include "types.h"
#include <string.h>

void draw_text(int x, int y, int font, char *text, struct color color)
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
