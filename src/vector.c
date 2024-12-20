#include "ec/vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ec_vector ec_vector_create(size_t element_size)
{
    size_t initial_capacity = 2;
    size_t initial_size = element_size * initial_capacity;
    void *buffer = malloc(initial_size);

    ec_vector vector = {buffer, element_size, 0, initial_capacity};

    return vector;
}

ec_vector ec_vector_clone(const ec_vector *vector)
{
    ec_vector clone = *vector;

    clone.buffer = malloc(clone.capacity * clone.element_size);

    memcpy(clone.buffer, vector->buffer, clone.size * clone.element_size);

    return clone;
}

void ec_vector_push(ec_vector *vector, void *element)
{
    if (vector->size >= vector->capacity)
    {
        vector->capacity *= 2;
        vector->buffer =
            realloc(vector->buffer, vector->capacity * vector->element_size);
    }

    memcpy(vector->buffer + vector->size * vector->element_size, element,
           vector->element_size);

    vector->size++;
}

void *ec_vector_at(const ec_vector *vector, int index)
{
    int final_index = index < 0 ? vector->size - index : index;

    return vector->buffer + final_index * vector->element_size;
}

ec_vector ec_vector_sort(const ec_vector *vector,
                         int (*compare)(const void *, const void *))
{
    ec_vector clone = ec_vector_clone(vector);

    qsort(clone.buffer, clone.size, clone.element_size, compare);

    return clone;
}

ec_vector ec_vector_map(const ec_vector *vector, size_t element_size,
                        void *(*convert)(const void *))
{
    ec_vector result = ec_vector_create(element_size);

    for (size_t i = 0; i < vector->size; i++)
    {
        ec_vector_push(&result, convert(ec_vector_at(vector, i)));
    }

    return result;
}

ec_vector ec_vector_filter(const ec_vector *vector,
                           bool (*filter)(const void *element, size_t index,
                                          void *data),
                           void *data)
{
    ec_vector result = ec_vector_create(vector->element_size);

    for (size_t i = 0; i < vector->size; i++)
    {
        void *element = ec_vector_at(vector, i);

        if (filter(element, i, data))
        {
            ec_vector_push(&result, element);
        }
    }

    return result;
}

void ec_vector_free(ec_vector *vector)
{
    free(vector->buffer);
    vector->size = 0;
    vector->capacity = 0;
}
