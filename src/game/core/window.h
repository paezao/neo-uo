#ifndef _CORE_WINDOW_H_
#define _CORE_WINDOW_H_

#include <GLFW/glfw3.h>
#include <stdbool.h>

struct window
{
    GLFWwindow *handle;
    int width;
    int height;
};

struct window * open_window(int width, int height, char * title);
void close_window(struct window * window);
bool window_should_close(struct window * window);

#endif
