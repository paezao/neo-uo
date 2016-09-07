#ifndef _CORE_WINDOW_H_
#define _CORE_WINDOW_H_

#include <GLFW/glfw3.h>
#include <stdbool.h>

typedef struct Window
{
    GLFWwindow *handle;
    int width;
    int height;
} Window;

Window * open_window(int width, int height, char * title);
void close_window(Window * window);
bool window_should_close(Window * window);

#endif
