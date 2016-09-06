#ifndef _DRAWING_H_
#define _DRAWING_H_

#include <GLFW/glfw3.h>
#include "window.h"

typedef struct Color 
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
} Color;

typedef struct Point2D
{
    float x;
    float y;
} Point2D;

#define GRAY  (Color){ 130, 130, 130, 255 }
#define BLACK (Color){ 0, 0, 0, 255 }
#define RED   (Color){ 255, 0, 0, 255 }
#define GREEN (Color){ 0, 255, 0, 255 }
#define BLUE  (Color){ 0, 0, 255, 255 }

void begin_drawing(struct Window * window);
void end_drawing(struct Window * window);
void clear_background(Color color);
void draw_rectangle(Point2D position, float width, float height, Color color);
void begin_3d(struct Window * window);
void end_3d();

#endif
