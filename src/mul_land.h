#ifndef __MUL_LAND_H__
#define __MUL_LAND_H__

#include "raylib.h"

static Texture2D land_textures[0x10000];

void unload_land_textures();
Texture2D get_land_texture(int index);
Texture2D load_land_texture(int index);

#endif
