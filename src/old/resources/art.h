#ifndef __ART_H__
#define __ART_H__

#include "raylib.h"

static Texture2D textures[0x3FFF];

void InitLandTextures();
void UnloadLandTextures();
Texture2D * GetLandTexture(int index);
static Texture2D LoadLandTexture(int index);

#endif
