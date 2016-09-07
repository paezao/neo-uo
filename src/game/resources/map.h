#ifndef _RESOURCES_MAP_H_
#define _RESOURCES_MAP_H_

#include "../core/types.h"

#define MAP_WIDTH_IN_TILES 7168
#define MAP_HEIGHT_IN_TILES 4096

typedef struct Tile
{
    uint16_t texture_id; 
    int8_t z;
} Tile;

typedef struct Map
{
    struct Tile tiles[MAP_WIDTH_IN_TILES][MAP_HEIGHT_IN_TILES];    
} Map;

Map * load_map();

#endif
