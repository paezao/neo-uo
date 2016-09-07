#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "core/window.h"
#include "core/input.h"
#include "resources/map.h"
#include "world.h"

struct game_state
{
    Window * window;
    Map * map;
    int player_x;
    int player_y;
};

static struct game_state *game_init()
{
    printf("Initializing Game\n");
    struct game_state *state = malloc(sizeof(*state));
    state->window = open_window(800, 450, "Neo UO");
    state->map = load_map();
    state->player_x = 1323;
    state->player_y = 1624;
    return state;
}

static void game_finalize(struct game_state *state)
{
    printf("Finalizing Game\n");
    close_window(state->window);
    free(state->map);
    free(state);
}

static void game_reload(struct game_state *state)
{
    printf("Reloading Game\n");
}

static void game_unload(struct game_state *state)
{
    printf("Unloading Game\n");
}

static bool game_step(struct game_state *state)
{
    if(window_should_close(state->window) || 
            is_key_down(state->window, KEY_ESCAPE))
    {
        return false;
    }

    begin_drawing(state->window);

    clear_background(BLACK);

    begin_3d(state->window);
    draw_world(state->window, state->map, state->player_x, state->player_y, 15);
    end_3d();

    end_drawing(state->window);

    glfwPollEvents();

    return true;
}

const struct game_api GAME_API = 
{
    .init = game_init,
    .reload = game_reload,
    .step = game_step,
    .unload = game_unload,
    .finalize = game_finalize
};
