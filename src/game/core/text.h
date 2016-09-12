#ifndef _CORE_TEXT_H_
#define _CORE_TEXT_H_

#include "drawing.h"

struct font
{
    struct texture * characters[224];
};

struct font ascii_fonts[10];

void draw_text(int x, int y, int font, char *text, struct color color);

#endif
