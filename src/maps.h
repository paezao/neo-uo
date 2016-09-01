#ifndef __MAPS_H__
#define __MAPS_H__

#include <stdint.h>

struct MulMapCell
{
    uint16_t tile_id;
    int8_t z;
};

struct MulMapBlock
{
    int32_t header;
    struct MulMapCell cells[64];
};

struct Map0
{
    struct MulMapBlock blocks[768][512];
};

struct Map0 * LoadMap0();

#endif
