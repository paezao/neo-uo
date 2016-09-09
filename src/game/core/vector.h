#ifndef _CORE_VECTOR_H_
#define _CORE_VECTOR_H_

typedef struct Vector
{
    void **items;
    int capacity;
    int total;
} Vector;

void vector_init(Vector *v);
int vector_total(Vector *v);
void vector_add(Vector *v, void *item);
void vector_set(Vector *v, int index, void *item);
void *vector_get(Vector *v, int index);
void vector_delete(Vector *v, int index);
void vector_free(Vector *v);

#endif
