#ifndef _CORE_VECTOR_H_
#define _CORE_VECTOR_H_

struct vector
{
    void **items;
    int capacity;
    int total;
};

void vector_init(struct vector *v);
int vector_total(struct vector *v);
void vector_add(struct vector *v, void *item);
void vector_set(struct vector *v, int index, void *item);
void *vector_get(struct vector *v, int index);
void vector_delete(struct vector *v, int index);
void vector_free(struct vector *v);

#endif
