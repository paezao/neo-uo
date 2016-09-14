#ifndef _CORE_TEXT_H_
#define _CORE_TEXT_H_

#include "drawing.h"
#include "math.h"

struct font
{
    struct texture * characters[224];
};

struct font ascii_fonts[10];

void draw_text(int x, int y, int font, char *text, struct color color);
struct size get_text_size(int font, const char *text);
char * format_text(char *text, ...);

#endif
