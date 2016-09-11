#include <stdlib.h>
#include <stdio.h>
#include "window.h"
#include "input.h"

static Window *current_window;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void window_size_callback(GLFWwindow* window, int width, int height)
{
    current_window->width = width;
    current_window->height = height;
}

Window * open_window(int width, int height, char * title)
{
    glfwInit();

    Window * window = (Window *)malloc(sizeof(Window));

    current_window = window;

    window->handle = glfwCreateWindow(width, height, title, NULL, NULL);
    window->width = width;
    window->height = height;

    glfwMakeContextCurrent(window->handle);

    int viewport_width, viewport_height;
    glfwGetFramebufferSize(window->handle, &viewport_width, &viewport_height);
    glViewport(0, 0, viewport_width, viewport_height);

    glfwSetFramebufferSizeCallback(window->handle, framebuffer_size_callback);
    glfwSetWindowSizeCallback(window->handle, window_size_callback);
    glfwSetKeyCallback(window->handle, key_callback);

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
