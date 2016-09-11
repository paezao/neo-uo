#ifndef _WORLD_H_
#define _WORLD_H_

#include "resources/map.h"
#include "core/drawing.h"
#include "core/texture.h"
#include "core/window.h"

void draw_world(Window *window, Map *map, int x, int y, int radius, bool hide_statics, bool hide_roofs, bool hide_walls);

#endif
