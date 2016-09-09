#include "world.h"
#include "resources/art.h"
#include "resources/tex_map.h"
#include <stdlib.h>
#include <stdio.h>

void draw_world(Window *window, Map *map, int x, int y, int radius)
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
            // tile.y -= 4 * z
            // tile.y -= (4 * z) + (4 * stackIndex) -> For items on ground
            // for stretching you stretch the current tile to match z to the east, south east and south in UO coords
            // east, south east and south
            // then 3 of your 5 vertices render at the same Z (Y + offset)
            // as those neighbors
            
            int tiles_x = x - init_x;
            int tiles_y = y - init_y;

            int plot_x = anchor_x + ((tiles_x - tiles_y) * tile_width / 2);
            int plot_y = anchor_y + ((tiles_x + tiles_y) * tile_height / 2);

            /*
            if(plot_x < (- 2 * tile_width) || plot_x > window->width + (2 * tile_width) ||
                    plot_y < (- 2 * tile_height) || plot_y > window->height + (2 * tile_height))
            {
                continue;
            }
            */

            Color color = WHITE;
            if(x == center_x && y == center_y) color = RED;

            int current_land_z = map->tiles[x][y].z;
            int east_land_z = map->tiles[x + 1][y].z;
            int south_east_land_z = map->tiles[x + 1][y + 1].z;
            int south_land_z = map->tiles[x][y + 1].z;

            int land_z = (current_land_z - center_z) * 4;

            if(map->tiles[x][y].texture_id < 3 || 
                    (map->tiles[x][y].texture_id >= 0x1AF && map->tiles[x][y].texture_id <= 0x1B5)) continue;

            if((current_land_z != east_land_z ||
                    current_land_z != south_east_land_z ||
                    current_land_z != south_land_z))
            {
                int east_offset = 0, south_east_offset = 0, south_offset = 0;
                if(current_land_z != east_land_z) east_offset = (current_land_z - east_land_z) * 4;
                if(current_land_z != south_east_land_z) south_east_offset = (current_land_z - south_east_land_z) * 4;
                if(current_land_z != south_land_z) south_offset = (current_land_z - south_land_z) * 4;

                Texture *tex_map_texture = get_tex_map_texture(map->tiles[x][y].texture_id);
                if (!tex_map_texture) continue;

                Rect tex_map_rect = {plot_x, plot_y - land_z, tile_width, tile_height};
                draw_tex_map(tex_map_rect, east_offset, south_east_offset, south_offset, tex_map_texture, color);
            }
            else
            {
                Texture *land_texture = get_land_texture(map->tiles[x][y].texture_id);
                if (!land_texture) continue;


                Rect land_rect = {plot_x, plot_y - land_z, tile_width, tile_height};
                draw_rectangle(land_rect, land_texture, color);
            }

            if(map->statics[x][y].texture_id == 0) continue;

            Texture *static_texture = get_static_texture(map->statics[x][y].texture_id);
            if (!static_texture) continue;

            int static_z = (map->statics[x][y].z - center_z) * 4;

            int static_y_offset = (static_texture->height / 2) - (tile_height / 2);
            Rect static_rect = {plot_x, plot_y - static_y_offset - static_z, static_texture->width, static_texture->height};
            draw_rectangle(static_rect, static_texture, WHITE);
        }
    }
}
