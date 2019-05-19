//
// Created by linuxlite on 05-04-2019.
//

#ifndef KLOTSKI_VECTOR_H
#define KLOTSKI_VECTOR_H

#include "utils.h"

typedef struct _item {
    struct _item *prev;
    void *value;
    struct _item *next;
} item;

typedef struct _vector {
    unsigned int size;
    item *first;
    item *last;
} vector;

void * at(vector *vec, unsigned int pos);

void insert(vector *vec, void *itm, int key);

void add(vector *vec, void *itm);

void *rem(vector *vec, unsigned int pos);

#define VECTOR(X) vector X = {.size = 0, .first = 0, .last = 0}

#endif //KLOTSKI_VECTOR_H
