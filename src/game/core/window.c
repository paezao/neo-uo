#include <stdlib.h>
#include "window.h"

struct Window * open_window(int width, int height, char * title)
{
    glfwInit();

    struct Window * window = (struct Window *)malloc(sizeof(struct Window));

    window->handle = glfwCreateWindow(width, height, title, NULL, NULL);
    window->width = width;
    window->height = height;

    glfwMakeContextCurrent(window->handle);

    int viewport_width, viewport_height;
    glfwGetFramebufferSize(window->handle, &viewport_width, &viewport_height);
    glViewport(0, 0, viewport_width, viewport_height);

    return window;
}

void close_window(struct Window * window)
{
    glfwDestroyWindow(window->handle);
    glfwTerminate();
    free(window);
}

bool window_should_close(struct Window * window)
{
    return glfwWindowShouldClose(window->handle);
}
