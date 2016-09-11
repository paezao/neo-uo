#ifndef _RESOURCES_TILE_DATA_H_
#define _RESOURCES_TILE_DATA_H_

#include "../core/types.h"

#define FLAG_NONE         0x00000000
#define FLAG_BACKGROUND   0x00000001
#define FLAG_WEAPON       0x00000002
#define FLAG_TRANSPARENT  0x00000004
#define FLAG_TRANSLUCENT  0x00000008
#define FLAG_WALL         0x00000010
#define FLAG_DAMAGING     0x00000020
#define FLAG_IMPASSABLE   0x00000040
#define FLAG_WET          0x00000080
#define FLAG_UNKNOWN1     0x00000100
#define FLAG_SURFACE      0x00000200
#define FLAG_BRIDGE       0x00000400
#define FLAG_GENERIC      0x00000800
#define FLAG_WINDOW       0x00001000
#define FLAG_NOSHOOT      0x00002000
#define FLAG_ARTICLE_A    0x00004000
#define FLAG_ARTICLE_AN   0x00008000
#define FLAG_INTERNAL     0x00010000
#define FLAG_FOLIAGE      0x00020000
#define FLAG_PARTIAL_HUE  0x00040000
#define FLAG_UNKNOWN2     0x00080000
#define FLAG_MAP          0x00100000
#define FLAG_CONTAINER    0x00200000
#define FLAG_WEARABLE     0x00400000
#define FLAG_LIGHT_SOURCE 0x00800000
#define FLAG_ANIMATION    0x01000000
#define FLAG_NO_DIAGONAL  0x02000000
#define FLAG_UNKNOWN3     0x04000000
#define FLAG_ARMOR        0x08000000
#define FLAG_ROOF         0x10000000
#define FLAG_DOOR         0x20000000
#define FLAG_STAIR_BACK   0x40000000
#define FLAG_STAIR_RIGHT  0x80000000

typedef struct LandTileData
{
    uint32 flags;
    uint16 texture_id; 
    char name[20];

} LandTileData;

typedef struct StaticTileData
{
    uint32 flags;
    uint8 weight;
    uint8 quality;
    int16 unknown1;
    uint8 unknown2;
    uint8 quantity;
    int16 animation;
    uint8 unknown3;
    uint8 hue;
    uint8 unknown4;
    uint8 unknown5;
    uint8 height;
    char name[20];

} StaticTileData;

static LandTileData land_tile_data[0x4000];
static StaticTileData static_tile_data[0x4000];

void load_tile_data();

LandTileData * get_land_tile_data(int index);
StaticTileData * get_static_tile_data(int index);

void unload_tile_data();

#endif
