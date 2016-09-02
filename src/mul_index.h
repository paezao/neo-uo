#ifndef __MUL_INDEX_H__
#define __MUL_INDEX_H__

#include <stdint.h>

struct MulIndexEntry
{
    int32_t lookup;
    int32_t length;
    int32_t extra;
};

struct MulTexMap
{
    int width;
    int height;
    uint8_t *data;
};

#endif
