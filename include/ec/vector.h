#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef struct ec_vector
{
    void *buffer;
    size_t element_size;
    size_t size;
    size_t capacity;
} ec_vector;

ec_vector ec_vector_create(size_t element_size);

ec_vector ec_vector_clone(const ec_vector *vector);

void ec_vector_push(ec_vector *vector, void *element);

void *ec_vector_at(const ec_vector *vector, int index);

ec_vector ec_vector_sort(const ec_vector *vector,
                         int (*compare)(const void *a, const void *b));

ec_vector ec_vector_map(const ec_vector *input, size_t element_size,
                        void *(*convert)(const void *));

ec_vector ec_vector_filter(const ec_vector *input,
                           bool (*filter)(const void *element, size_t index,
                                          void *data),
                           void *data);

void ec_vector_free(ec_vector *vector);
