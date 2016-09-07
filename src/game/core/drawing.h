#ifndef _CORE_DRAWING_H_
#define _CORE_DRAWING_H_

#include <GLFW/glfw3.h>
#include "window.h"
#include "texture.h"

typedef struct Color 
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
} Color;

typedef struct Rect
{
    float x;
    float y;
    float width;
    float height;
} Rect;

#define WHITE (Color){ 255, 255, 255, 255 }
#define GRAY  (Color){ 130, 130, 130, 255 }
#define BLACK (Color){ 0, 0, 0, 255 }
#define RED   (Color){ 255, 0, 0, 255 }
#define GREEN (Color){ 0, 255, 0, 255 }
#define BLUE  (Color){ 0, 0, 255, 255 }

void begin_drawing(struct Window * window);
void end_drawing(struct Window * window);
void clear_background(Color color);
void draw_rectangle(Rect rect, Texture *texture, Color color);
void begin_3d(struct Window * window);
void end_3d();

#endif
