#ifndef _RESOURCES_ART_H_
#define _RESOURCES_ART_H_

#include "../core/texture.h"

static struct texture * land_textures[0x3FFF];
static struct texture * static_textures[0x3FFF];

struct texture * get_land_texture(int index);
void unload_land_textures();

struct texture * get_static_texture(int index);
void unload_static_textures();

#endif
