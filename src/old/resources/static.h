#ifndef __STATIC_H__
#define __STATIC_H__

#include "raylib.h"

static Texture2D textures[0x10000];

void UnloadStaticTextures();
Texture2D GetStaticTexture(int index);
static Texture2D LoadStaticTexture(int index);

#endif
