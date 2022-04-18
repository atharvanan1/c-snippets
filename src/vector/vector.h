#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>

typedef struct Vector {
  int* data;
  size_t size;
  size_t capacity;
} Vector;

Vector* vector_init(size_t capacity);
int vector_pop(Vector* vector);
int vector_get(Vector* vector, size_t element_num, int* dest);
int vector_append(Vector* vector, int element);
int vector_insert(Vector* vector, int element, size_t pos);
int vector_remove(Vector* vector, size_t pos);
int vector_delete(Vector*);

#endif // VECTOR_H_
