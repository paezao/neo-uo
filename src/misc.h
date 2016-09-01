#ifndef __MISC_H__
#define __MISC_H__

#include "raylib.h"
#include "rlgl.h"

void Begin3dOrthoMode();
void DrawGroundTile(Texture2D texture, Rectangle sourceRec, Rectangle destRec, Color tint);

#endif
