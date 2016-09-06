#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <GLFW/glfw3.h>
#include <stdbool.h>

struct Window
{
    GLFWwindow *handle;
    int width;
    int height;
};

struct Window * open_window(int width, int height, char * title);
void close_window(struct Window * window);
bool window_should_close(struct Window * window);

#endif
