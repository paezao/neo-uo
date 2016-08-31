#include <stdint.h>

struct MulIndexEntry {
    int32_t lookup;
    int32_t length;
    int32_t extra;
};

struct MulTexMap {
    int width;
    int height;
    uint8_t *data;
};

struct MulIndexEntry mul_index_entry(const char *path, int entry_id);
struct MulTexMap mul_tex_map(const char *path, struct MulIndexEntry index);
