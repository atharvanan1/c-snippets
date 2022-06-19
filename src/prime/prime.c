#include "prime.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
// TODO: make sieve of erathothenes and add the following functions:
// prime_init(int num) -> prime object (what does prime object contain? we don't know yet)
// prime_get_next(prime object) -> int (prime number is returned, status is updated) int or -1 with errno
// prime_get_nth(int n) -> this will create a sieve and return (maybe we can try to get optimized Rust)
// prime_deinit(prime object);
// maybe follow rust functions?

#define BASE_PRIME {2, 3, 5, 7}

static void _prime_process_array(bool *num_array, int capacity)
{
  // Treat base prime numbers
  num_array[0] = false;
  num_array[1] = false;
  num_array[2] = true;
  num_array[3] = true;
  for (int i = 2; i < capacity / 2; i++)
  {
    for(int multiply = 2; multiply < capacity / 2; multiply++)
    {
      int index = i * multiply;
      if (index < capacity)
        num_array[index] = false;
      else
        break;
    }
  }
}

PrimeSieve* prime_init(int num)
{
  PrimeSieve* ret_sieve = NULL;
  ret_sieve = (PrimeSieve*) malloc(sizeof(PrimeSieve) * num);
  ret_sieve->num_array = (bool *) calloc(num, sizeof(bool));
  memset(ret_sieve->num_array, (int) true, num);
  ret_sieve->next_prime = 2;
  ret_sieve->capacity = num;
  _prime_process_array(ret_sieve->num_array, ret_sieve->capacity);
  return ret_sieve;
}

int prime_get_next(PrimeSieve* sieve)
{
  int ret_next_prime = sieve->next_prime;
  for(int i = sieve->next_prime + 1; i < sieve->capacity; i++)
  {
    if (sieve->num_array[i]) {
      sieve->next_prime = i;
      break;
    }
    if (i == ret_next_prime)
    {
      return -1;
    }
  }
  return ret_next_prime;
}

int prime_get_last(PrimeSieve* sieve)
{
  int old_prime = 0;
  for (int i = 0; i < sieve->capacity; i++) 
  {
    if (sieve->num_array[i])
    {
      old_prime = i;
    }
  }
  return old_prime;
}

int prime_get_nth(int n)
{

}

void prime_iterator_reset(PrimeSieve *sieve)
{
  sieve->next_prime = 2;
}

void prime_deinit(PrimeSieve* sieve)
{
  if (sieve == NULL)
  {
    return;
  }
  free(sieve->num_array);
  free(sieve);
}
