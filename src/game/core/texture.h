#ifndef _CORE_TEXTURE_H_
#define _CORE_TEXTURE_H_

#include "types.h"

typedef struct Texture
{
    uint32 id;
    uint32 width;
    uint32 height;
} Texture;

Texture * load_texture(void *data, uint32 width, uint32 height);
void unload_texture(Texture *texture);

#endif
