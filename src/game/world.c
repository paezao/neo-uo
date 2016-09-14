#include "world.h"
#include "resources/art.h"
#include "resources/tex_map.h"
#include "resources/tile_data.h"
#include "core/text.h"
#include "core/math.h"
#include <stdlib.h>
#include <stdio.h>

void draw_world(struct window *window, struct map *map, int x, int y, int radius, bool hide_statics, bool hide_roofs, bool hide_walls, bool show_z, struct vector2 mouse_pos)
{
    int init_x = x - radius;
    int init_y = y - radius;
    int end_x = x + radius;
    int end_y = y + radius;
    int tile_width = 44;
    int tile_height = 44;

    int anchor_x = window->width / 2;
    int anchor_y = window->height / 2 - radius * tile_height;

    int center_x = x;
    int center_y = y;
    int center_z = map->tiles[x][y].z;

    for(int y = init_y; y <= end_y; y++)
    {
        for(int x = init_x; x <= end_x; x++)
        {
            int tiles_x = x - init_x;
            int tiles_y = y - init_y;

            int plot_x = anchor_x + ((tiles_x - tiles_y) * tile_width / 2);
            int plot_y = anchor_y + ((tiles_x + tiles_y) * tile_height / 2);

            struct color color = WHITE;

            int current_land_z = map->tiles[x][y].z;
            int east_land_z = map->tiles[x + 1][y].z;
            int south_east_land_z = map->tiles[x + 1][y + 1].z;
            int south_land_z = map->tiles[x][y + 1].z;

            int land_z = (current_land_z - center_z) * 4;

            if(plot_x < (- 2 * tile_width) || plot_x > window->width + (2 * tile_width) ||
                    (plot_y - land_z) < (- 2 * tile_height) || (plot_y - land_z) > window->height + (2 * tile_height))
            {
                continue;
            }

            // Mouse Picking tests
            if(mouse_pos.x >= (plot_x - (tile_width / 2)) && mouse_pos.x <= (plot_x + (tile_width / 2)) &&
                    mouse_pos.y >= ((plot_y - land_z) - (tile_height / 2)) && mouse_pos.y <= ((plot_y - land_z) + (tile_height / 2)))
                color = GREEN;
            
            // Current Tile Coloring
            if(x == center_x && y == center_y) color = RED;

            int land_tile_id = map->tiles[x][y].texture_id;
            int land_no_draw = (land_tile_id < 3 || (land_tile_id >= 0x1AF && land_tile_id <= 0x1B5));
            
            if((current_land_z != east_land_z ||
                    current_land_z != south_east_land_z ||
                    current_land_z != south_land_z))
            {
                int east_offset = 0, south_east_offset = 0, south_offset = 0;
                if(current_land_z != east_land_z) east_offset = (current_land_z - east_land_z) * 4;
                if(current_land_z != south_east_land_z) south_east_offset = (current_land_z - south_east_land_z) * 4;
                if(current_land_z != south_land_z) south_offset = (current_land_z - south_land_z) * 4;

                struct texture *tex_map_texture = get_tex_map_texture(map->tiles[x][y].texture_id);
                if (!tex_map_texture) continue;

                struct rectangle tex_map_rect = {plot_x, plot_y - land_z, tile_width, tile_height};
                if(!land_no_draw) draw_tex_map(tex_map_rect, east_offset, south_east_offset, south_offset, tex_map_texture, color);
            }
            else
            {
                if(map->tiles[x][y].texture_id < 3 || 
                        (map->tiles[x][y].texture_id >= 0x1AF && map->tiles[x][y].texture_id <= 0x1B5)) continue;

                struct texture *land_texture = get_land_texture(map->tiles[x][y].texture_id);
                if (!land_texture) continue;

                struct rectangle land_rect = {plot_x, plot_y - land_z, tile_width, tile_height};
                if(!land_no_draw) draw_texture(land_rect, land_texture, color);
            }

            if(show_z) 
            {
                if((x > (center_x  - 4) && x < (center_x + 4) && y > (center_y - 4) && y < (center_y + 4)))
                {
                    struct size text_size = get_text_size(0, format_text("%d", current_land_z));
                    draw_text(plot_x - (text_size.width / 2), plot_y - land_z - (text_size.height / 2), 0, format_text("%d", current_land_z), WHITE);
                }
            }

            struct tile *tile = &map->tiles[x][y];

            if(!hide_statics)
            { 
                int draw_max_altitude = 255;

                if(hide_roofs)
                    draw_max_altitude = current_land_z - (current_land_z % 20) + 20;

                for(int i=0; i < vector_total(&tile->statics); i++)
                {
                    struct item *_static = vector_get(&tile->statics, i);
                    struct static_tile_data *static_tile_data = get_static_tile_data(_static->texture_id);

                    if(hide_roofs && (static_tile_data->flags & FLAG_ROOF)) continue;
                    if(hide_walls && (static_tile_data->flags & FLAG_WALL)) continue;

                    //if(_static->texture_id < 3) continue;
                    if(_static->texture_id < 3 || (_static->texture_id >= 0x1AF && _static->texture_id <= 0x1B5)) continue;

                    struct texture *static_texture = get_static_texture(_static->texture_id);
                    if (!static_texture) continue;

                    int static_z = (_static->z - center_z) * 4;

                    if(static_z <= draw_max_altitude)
                    {
                        int static_y_offset = (static_texture->height / 2) - (tile_height / 2);
                        struct rectangle static_rect = {plot_x, plot_y - static_y_offset - static_z, static_texture->width, static_texture->height};
                        draw_texture(static_rect, static_texture, WHITE);
                    }
                }
            }
        }
    }
}

void draw_tex_map(struct rectangle rect, int east_offset, int south_east_offset, int south_offset, struct texture *texture, struct color color)
{
    struct vector3 vertices[4] = {
        {rect.x, rect.y - (rect.width / 2), -1.0f},
        {rect.x - (rect.width / 2), rect.y + south_offset, -1.0f},
        {rect.x, rect.y + (rect.height / 2) + south_east_offset, -1.0f},
        {rect.x + (rect.width / 2), rect.y + east_offset, -1.0f}
    };

    draw_texture_adv(vertices, texture, color);
}
