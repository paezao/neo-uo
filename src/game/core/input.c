#include "input.h"

bool is_key_down(struct Window * window, int key)
{
    return glfwGetKey(window->handle, key);
}

bool is_key_up(struct Window * window, int key)
{
    return !glfwGetKey(window->handle, key);
}
