#ifndef _RESOURCES_TEX_MAP_H_
#define _RESOURCES_TEX_MAP_H_

#include "../core/texture.h"

static Texture * tex_map_textures[0x3FFF];

Texture * get_tex_map_texture(int index);
void unload_tex_map_textures();

#endif
