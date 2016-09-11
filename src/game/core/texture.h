#ifndef _CORE_TEXTURE_H_
#define _CORE_TEXTURE_H_

#include "types.h"

struct texture
{
    uint32 id;
    uint32 width;
    uint32 height;
};

struct texture * load_texture(void *data, uint32 width, uint32 height);
void unload_texture(struct texture *texture);

#endif
