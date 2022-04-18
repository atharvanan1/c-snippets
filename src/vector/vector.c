#include "vector.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// TODO: add following functions
// Vector* vector_init(size_t capacity);
// int vector_pop(Vector* vector);
// int vector_get(Vector* vector, size_t element_num);
// int vector_append(Vector* vector, int element);
// int vector_insert(Vector* vector, int element, size_t pos);
// int vector_remove(Vector* vector, size_t pos);
// static int _vector_resize(Vector* vector, size_t new_size);
// int vector_delete(Vector*);

#define SIZE_CHUNK 256 // Always keep it multiple of 2

/*
 * _round_capacity
 *
 * rounds capacity to nearest "size chunk"
 *
 * capacity: size_t, will be the capacity requested
 *
 * Returns new capacity
 *
 */
static inline size_t
_round_capacity (size_t capacity)
{
  return ((capacity >> 8) + 1) << 8;
}

/*
 * _vector_resize
 *
 * resize the vector data
 *
 * vector: vector to be resized
 * new_size: new size will be capacity + SIZE_CHUNK
 *
 * Returns 0 on success, -1 with errno set
 *
 */
static inline int
_vector_resize(Vector* vector, size_t new_size)
{
  if (vector == NULL) {
    errno = EINVAL;
    return -1;
  }

  int* new_data = (int*) realloc(vector->data, new_size);
  if (new_data == NULL) {
    errno = ENOMEM;
    return -1;
  }
  vector->data = new_data;
  return 0;
}

/*
 * vector_init
 *
 * returns pointer to Vector structure with capacity
 * multiple of 256
 *
 * capacity: size_t, will be the capacity requested
 *
 * Returns pointer to allocated vector, NULL if error with errno set
 *
 */
Vector*
vector_init(size_t capacity)
{
  Vector* ret_vec = NULL;
  ret_vec = (Vector*) calloc(1, sizeof(Vector));
  if (ret_vec == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  ret_vec->data = NULL;
  capacity = _round_capacity(capacity);
  ret_vec->data = (int*) calloc(capacity, sizeof(int));
  ret_vec->capacity = capacity;
  return ret_vec;
}

/*
 * vector_insert
 *
 * inserts an element at position
 *
 * vector: vector that was initialized previously
 * element: int element to be added
 * pos: position to be added
 *
 * Returns 0 on success, -1 on failure with errno
 *
 */
int
vector_insert(Vector* vector, int element, size_t pos)
{
  if (vector == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (vector->size + 1 == vector->capacity) {
    if (_vector_resize(vector, vector->capacity + SIZE_CHUNK)) {
      // pass the carried errno
      errno = errno;
      return -1;
    }
  }

  char* temp = (char*) malloc(sizeof(char) * (vector->size - pos));
  if (temp == NULL) {
      errno = ENOMEM;
      return -1;
  }

  memcpy(temp, vector->data + pos, vector->size - pos);
  memcpy(vector->data + pos + 1, temp, vector->size - pos);
  vector->data[pos] = element;
  vector->size++;

  return 0;
}

/*
 * vector_remove
 *
 * Remove an element from vector
 *
 * vector: vector to be used
 * pos: position to remove
 *
 * Return the element
 *
 */
int vector_remove(Vector* vector, size_t pos)
{
  if (vector == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (vector->size + 1 == vector->capacity) {
    if (_vector_resize(vector, vector->capacity + SIZE_CHUNK)) {
      // pass the carried errno
      errno = errno;
      return -1;
    }
  }

  char* temp = (char*) malloc(sizeof(char) * (vector->size - pos));
  if (temp == NULL) {
      errno = ENOMEM;
      return -1;
  }

  memcpy(temp, vector->data + pos, vector->size - pos);
  memcpy(vector->data + pos - 1, temp, vector->size - pos);
  vector->data[vector->size - 1] = 0;
  int element = vector->data[pos];
  vector->size--;

  return element;
}

/*
 * vector_pop
 *
 * pops an element at the end
 *
 * vector: vector that shall be pop'ed
 *
 * returns the element
 */
int vector_pop(Vector* vector)
{
  if (vector == NULL)
    return 0;
  int element = vector->data[vector->size - 1];
  vector_remove(vector, vector->size -1);
  return element;
}

/*
 * vector_get
 *
 * get the vector element
 *
 * vector: vector to get element from
 * element_num: element number to fetch
 * dest: destination where element shall be copied
 *
 * Return
 */
int vector_get(Vector* vector, size_t element_num, int* dest)
{
  if (element_num > vector->size)
  {
    errno = EINVAL;
    return -1;
  }
  if (dest == NULL)
  {
    errno = EINVAL;
    return -1;
  }
  *dest = vector->data[element_num];
  return 0;
}

/*
 * vector_append
 *
 * append the element to the end
 *
 * vector: vector that shall be appended
 * element: int element that shall be added
 *
 * Return 0 on success, -1 on failure
 */
int vector_append(Vector* vector, int element)
{
  if (vector == NULL) {
    errno = EINVAL;
    return -1;
  }
  return vector_insert(vector, element, vector->size - 1);
}

/*
 * vector_delete
 *
 * Delete the vector structure
 *
 * vector: vector to be deleted
 *
 * Returns 0 on success, however free function doesn't
 * return any values
 */
int vector_delete(Vector* vector)
{
  if (vector == NULL)
    return -1;
  if (vector->data == NULL)
    return -1;
  free(vector->data);
  free(vector);
  return 0;
}
