#ifndef _CORE_DRAWING_H_
#define _CORE_DRAWING_H_

#include <GLFW/glfw3.h>
#include "window.h"
#include "texture.h"

struct color 
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
};

struct rectangle
{
    float x;
    float y;
    float width;
    float height;
};

#define WHITE (struct color){ 255, 255, 255, 255 }
#define GRAY  (struct color){ 130, 130, 130, 255 }
#define BLACK (struct color){ 0, 0, 0, 255 }
#define RED   (struct color){ 255, 0, 0, 255 }
#define GREEN (struct color){ 0, 255, 0, 255 }
#define BLUE  (struct color){ 0, 0, 255, 255 }

void begin_drawing(struct window * window);
void end_drawing(struct window * window);
void clear_background(struct color color);
void draw_rectangle(struct rectangle rect, struct texture *texture, struct color color);
void draw_tex_map(struct rectangle rect, int east_offset, int south_east_offset, int south_offset, struct texture *texture, struct color color);
void begin_3d(struct window * window);
void end_3d();

#endif
