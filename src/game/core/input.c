#include "input.h"

void update_input()
{
    last_key_pressed = -1;

    for (int i = 0; i < 512; i++) previous_key_state[i] = current_key_state[i];

    glfwPollEvents();
}

bool is_key_down(struct window * window, int key)
{
    return glfwGetKey(window->handle, key);
}

bool is_key_up(struct window * window, int key)
{
    return !glfwGetKey(window->handle, key);
}

bool is_key_pressed(struct window * window, int key)
{
    return ((current_key_state[key] != previous_key_state[key]) && (current_key_state[key] == 1));
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    current_key_state[key] = action;
    if (action == GLFW_PRESS) last_key_pressed = key;
}
