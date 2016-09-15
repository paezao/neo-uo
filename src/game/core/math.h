#ifndef _CORE_MATH_H_
#define _CORE_MATH_H_

struct rectangle
{
    float x;
    float y;
    float width;
    float height;
};

struct vector3
{
    float x;
    float y;
    float z;
};

struct vector2
{
    float x;
    float y;
};

struct point2
{
    float x;
    float y;
};

struct size
{
    float width;
    float height;
};

struct triangle
{
    struct point2 p1;
    struct point2 p2;
    struct point2 p3;
};

#endif
