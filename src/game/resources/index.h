#ifndef _RESOURCES_INDEX_H_
#define _RESOURCES_INDEX_H_

#include "../core/types.h"

struct index_entry
{
    int32 lookup;
    int32 length;
    int32 extra;
};

struct index_entry get_index_entry(char *filepath, int index);

#endif
