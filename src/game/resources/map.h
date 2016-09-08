#ifndef _RESOURCES_MAP_H_
#define _RESOURCES_MAP_H_

#include "../core/types.h"

#define MAP_WIDTH_IN_TILES 7168
#define MAP_HEIGHT_IN_TILES 4096

typedef struct Tile
{
    uint16 texture_id; 
    int8 z;
} Tile;

typedef struct Static
{
    uint16 texture_id; 
    int8 z;
} Static;

typedef struct Map
{
    struct Tile tiles[MAP_WIDTH_IN_TILES][MAP_HEIGHT_IN_TILES];    
    struct Static statics[MAP_WIDTH_IN_TILES][MAP_HEIGHT_IN_TILES];    
} Map;

Map * load_map();

#endif
