#include "index.h"
#include <stdio.h>

struct IndexEntry GetIndexEntry(char *path, int index)
{
    struct IndexEntry index_entry;

    FILE *index_fp = fopen(path, "r");
    fseek(index_fp, index * 12, SEEK_SET);
    fread(&index_entry.lookup, sizeof(int32_t), 1, index_fp);
    fread(&index_entry.length, sizeof(int32_t), 1, index_fp);
    fread(&index_entry.extra, sizeof(int32_t), 1, index_fp);

    fclose(index_fp);

    return index_entry;
}
