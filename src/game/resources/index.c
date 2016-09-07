#include "index.h"
#include <stdio.h>

IndexEntry get_index_entry(char *filepath, int index)
{
    IndexEntry index_entry;

    FILE *index_fp = fopen(filepath, "r");
    fseek(index_fp, index * 12, SEEK_SET);
    fread(&index_entry.lookup, sizeof(int32), 1, index_fp);
    fread(&index_entry.length, sizeof(int32), 1, index_fp);
    fread(&index_entry.extra, sizeof(int32), 1, index_fp);
    fclose(index_fp);

    return index_entry;
}
