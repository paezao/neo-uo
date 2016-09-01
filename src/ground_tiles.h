#ifndef __GROUND_TILES_H__
#define __GROUND_TILES_H__

#include "stdint.h"
#include "raylib.h"

struct GroundTile
{
    uint16_t id;
    Texture2D texture;
};

struct GroundTile * LoadGroundTiles();

#endif
