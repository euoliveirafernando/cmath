#include <stdlib.h>
#include <string.h>
#include "memory.h"

void * cmath_alloc(size_t size)
{
    void * data;

    data = malloc(size);

    if (data == NULL)
        error("failed to allocate");

    bzero(data, size);

    return data;
}

void * cmath_realloc(void * data, size_t size)
{
    data = realloc(data, size);

    if (data == NULL)
        error("failed to reallocate");

    return data;
}

void cmath_free(void * data)
{
    if (data != NULL)
        free(data);
}