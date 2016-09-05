#include "mul_index.h"
#include <stdio.h>

struct MulIndexEntry get_mul_index(char *path, int index)
{
    struct MulIndexEntry index_entry;

    FILE *index_fp = fopen(path, "r");
    fseek(index_fp, index * 12, SEEK_SET);
    fread(&index_entry.lookup, sizeof(int32_t), 1, index_fp);
    fread(&index_entry.length, sizeof(int32_t), 1, index_fp);
    fread(&index_entry.extra, sizeof(int32_t), 1, index_fp);

    return index_entry;
}
