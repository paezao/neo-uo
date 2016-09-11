#ifndef _RESOURCES_MAP_H_
#define _RESOURCES_MAP_H_

#include "../core/types.h"
#include "../core/vector.h"

#define MAP_WIDTH_IN_TILES 7168
#define MAP_HEIGHT_IN_TILES 4096

struct tile
{
    uint16 texture_id; 
    int8 z;
    struct vector statics;
};

struct item
{
    uint16 texture_id; 
    int8 z;
};

struct map
{
    struct tile tiles[MAP_WIDTH_IN_TILES][MAP_HEIGHT_IN_TILES];    
};

struct map * load_map();
void unload_map(struct map *map);

#endif
