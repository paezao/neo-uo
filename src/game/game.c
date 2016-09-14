#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "core/window.h"
#include "core/input.h"
#include "core/log.h"
#include "core/text.h"
#include "core/time.h"
#include "resources/map.h"
#include "resources/art.h"
#include "resources/tex_map.h"
#include "resources/tile_data.h"
#include "resources/fonts.h"
#include "world.h"

struct game_state
{
    struct window * window;
    struct map * map;
    int player_x;
    int player_y;
    bool hide_statics;
    bool hide_roofs;
    bool hide_walls;
    bool show_z;
};

static struct game_state *game_init()
{
    print_log(LOG_INFO, "Initializing Game");
    struct game_state *state = malloc(sizeof(*state));
    state->window = open_window(1280, 720, "Neo UO");
    print_log(LOG_INFO, "Loading Map");
    state->map = load_map();
    state->player_x = 1463;
    state->player_y = 1648;
    return state;
}

static void game_finalize(struct game_state *state)
{
    print_log(LOG_INFO, "Finalizing Game");
    close_window(state->window);
    free(state->map);
    free(state);
    unload_land_textures();
    unload_static_textures();
    unload_tex_map_textures();
    unload_map(state->map);
}

static void game_load(struct game_state *state)
{
    print_log(LOG_INFO, "Loading Game");
    print_log(LOG_INFO, "Loading Tile Data");
    load_tile_data();
    print_log(LOG_INFO, "Loading Ascii Fonts");
    load_ascii_fonts();
    init_time(60);
}

static void game_unload(struct game_state *state)
{
    print_log(LOG_INFO, "Unloading Game");
}

static bool game_step(struct game_state *state)
{
    begin_frame_time();

    begin_drawing(state->window);

    clear_background(BLACK);

    begin_3d(state->window);

    struct vector2 mouse_position = get_mouse_position(state->window);

    draw_world(state->window, state->map, state->player_x, state->player_y, 22, state->hide_statics, state->hide_roofs, state->hide_walls, state->show_z, mouse_position);

    // FPS
    draw_text(5, 5, 0, format_text("FPS %2.0f", get_fps()), WHITE);

    // Player Location
    draw_text(state->window->width - 220, 5, 0, format_text("Player %d x %d", state->player_x, state->player_y), WHITE);

    // Mouse Position
    draw_text(state->window->width - 220, state->window->height - 25, 0, format_text("Mouse %2.0f x %2.0f", mouse_position.x, mouse_position.y), WHITE);

    // Debug Options
    draw_text(5, state->window->height - 70, 0, "F1 Statics", WHITE);
    draw_text(120, state->window->height - 70, 0, state->hide_statics ? "OFF" : "ON", state->hide_statics ? RED : GREEN);
    draw_text(5, state->window->height - 55, 0, "F2 Roofs", WHITE);
    draw_text(120, state->window->height - 55, 0, state->hide_roofs ? "OFF" : "ON", state->hide_roofs ? RED : GREEN);
    draw_text(5, state->window->height - 40, 0, "F3 Walls", WHITE);
    draw_text(120, state->window->height - 40, 0, state->hide_walls ? "OFF" : "ON", state->hide_walls ? RED : GREEN);
    draw_text(5, state->window->height - 25, 0, "F4 Tile Z", WHITE);
    draw_text(120, state->window->height - 25, 0, state->show_z ? "ON" : "OFF", state->show_z ? GREEN : RED);

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
    if(is_key_pressed(state->window, KEY_F4)) { state->show_z = !state->show_z; }

    update_input();

    end_frame_time();

    return true;
}

const struct game_api GAME_API = 
{
    .init = game_init,
    .load = game_load,
    .step = game_step,
    .unload = game_unload,
    .finalize = game_finalize
};
