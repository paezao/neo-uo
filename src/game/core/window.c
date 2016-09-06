#include <stdlib.h>
#include <stdio.h>
#include "window.h"

Window * open_window(int width, int height, char * title)
{
    glfwInit();

    Window * window = (Window *)malloc(sizeof(Window));

    window->handle = glfwCreateWindow(width, height, title, NULL, NULL);
    window->width = width;
    window->height = height;

    glfwMakeContextCurrent(window->handle);

    int viewport_width, viewport_height;
    glfwGetFramebufferSize(window->handle, &viewport_width, &viewport_height);
    glViewport(0, 0, viewport_width, viewport_height);

    window->viewport_width = viewport_width;
    window->viewport_height = viewport_height;

    return window;
}

void close_window(Window * window)
{
    glfwDestroyWindow(window->handle);
    glfwTerminate();
    free(window);
}

bool window_should_close(Window * window)
{
    return glfwWindowShouldClose(window->handle);
}
