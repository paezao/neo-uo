#ifndef __INDEX_H__
#define __INDEX_H__

#include <stdint.h>

struct IndexEntry
{
    int32_t lookup;
    int32_t length;
    int32_t extra;
};

struct IndexEntry GetIndexEntry(char *path, int index);

#endif
