#include "world.h"
#include "resources/art.h"
#include <stdlib.h>

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

    for(int y = init_y; y <= end_y; y++)
    {
        for(int x = init_x; x <= end_x; x++)
        {
            int tiles_x = x - init_x;
            int tiles_y = y - init_y;

            int plot_x = anchor_x + ((tiles_x - tiles_y) * tile_width / 2);
            int plot_y = anchor_y + ((tiles_x + tiles_y) * tile_height / 2);

            if(plot_x < (- 2 * tile_width) || plot_x > window->width + (2 * tile_width) ||
                    plot_y < (- 2 * tile_height) || plot_y > window->height + (2 * tile_height))
            {
                continue;
            }

            Texture *texture = get_land_texture(map->tiles[x][y].texture_id);
            if (!texture) continue;

            Rect rect = {plot_x, 
                plot_y, 
                tile_width, 
                tile_height};

            draw_rectangle(rect, texture, WHITE);
        }
    }
}
