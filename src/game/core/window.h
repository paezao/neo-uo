#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <GLFW/glfw3.h>
#include <stdbool.h>

typedef struct Window
{
    GLFWwindow *handle;
    int width;
    int height;
    int viewport_width;
    int viewport_height;
} Window;

Window * open_window(int width, int height, char * title);
void close_window(Window * window);
bool window_should_close(Window * window);

#endif
