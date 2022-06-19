#ifndef PRIME_H_
#define PRIME_H_
#include <stdbool.h>

typedef struct PrimeSieve {
  bool *num_array;
  int next_prime;
  int capacity;
} PrimeSieve;

PrimeSieve* prime_init(int num);
int prime_get_next(PrimeSieve* sieve);
int prime_get_last(PrimeSieve* sieve);
void prime_iterator_reset(PrimeSieve *sieve);
void prime_deinit(PrimeSieve* sieve);

#endif // PRIME_H_
