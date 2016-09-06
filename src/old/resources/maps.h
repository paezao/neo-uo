#ifndef __MAPS_H__
#define __MAPS_H__

#include <stdint.h>

#define MAP_WIDTH_IN_TILES 7168
#define MAP_HEIGHT_IN_TILES 4096

struct Tile
{
    uint16_t texture_id; 
    int8_t z;
};

struct Map
{
    struct Tile tiles[MAP_WIDTH_IN_TILES][MAP_HEIGHT_IN_TILES];    
};

void LoadMap(struct Map * map);
void DrawMap(struct Map * map, int x, int y, int radius);

#endif
