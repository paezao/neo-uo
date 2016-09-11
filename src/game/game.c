#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "core/window.h"
#include "core/input.h"
#include "resources/map.h"
#include "resources/art.h"
#include "resources/tex_map.h"
#include "resources/tile_data.h"
#include "world.h"

struct game_state
{
    Window * window;
    Map * map;
    int player_x;
    int player_y;
    bool hide_statics;
    bool hide_roofs;
    bool hide_walls;
};

static struct game_state *game_init()
{
    printf("Initializing Game...");
    struct game_state *state = malloc(sizeof(*state));
    state->window = open_window(1280, 720, "Neo UO");
    printf("Done\n");
    printf("Loading Map...");
    state->map = load_map();
    printf("Done\n");
    state->player_x = 1463;
    state->player_y = 1648;
    return state;
}

static void game_finalize(struct game_state *state)
{
    printf("Finalizing Game\n");
    close_window(state->window);
    free(state->map);
    free(state);
    unload_land_textures();
}

static void game_reload(struct game_state *state)
{
    printf("Reloading Game\n");
    printf("Loading Tile Data...");
    load_tile_data();
    printf("Done\n");
}

static void game_unload(struct game_state *state)
{
    printf("Unloading Game\n");
}

static bool game_step(struct game_state *state)
{

    begin_drawing(state->window);

    clear_background(BLACK);

    begin_3d(state->window);

    draw_world(state->window, state->map, state->player_x, state->player_y, 22, state->hide_statics, state->hide_roofs, state->hide_walls);

    end_3d();

    end_drawing(state->window);

    if(window_should_close(state->window) || 
            is_key_pressed(state->window, KEY_ESCAPE))
    {
        return false;
    }

    if(is_key_down(state->window, KEY_UP)) { state->player_x -= 1; state->player_y -= 1; }
    if(is_key_down(state->window, KEY_DOWN)) { state->player_x += 1; state->player_y += 1; }
    if(is_key_down(state->window, KEY_LEFT)) { state->player_x -= 1; state->player_y += 1; }
    if(is_key_down(state->window, KEY_RIGHT)) { state->player_x += 1; state->player_y -= 1; }
    if(is_key_pressed(state->window, KEY_F1)) { state->hide_statics = !state->hide_statics; }
    if(is_key_pressed(state->window, KEY_F2)) { state->hide_roofs = !state->hide_roofs; }
    if(is_key_pressed(state->window, KEY_F3)) { state->hide_walls = !state->hide_walls; }

    update_input();

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
