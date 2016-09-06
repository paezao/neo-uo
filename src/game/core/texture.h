#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "types.h"

typedef struct Texture
{
    uint32 id;
    uint32 width;
    uint32 height;
} Texture;

Texture * load_texture(void *data, uint32 width, uint32 height);

#endif
