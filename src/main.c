#include <stdio.h>
#include "c_string/c_string.h"
#include "prime/prime.h"
#include "Config.h"
#include <time.h>

#define SIZE 100

int main(void)
{
    CString test_string = string_new(TEST_STRING);
    string_insert(&test_string, 4, 'M');
    string_insert(&test_string, 5, 'e');
    string_insert_str(&test_string, 6, "NOW!");
    printf("%s\n", test_string);
    string_delete(test_string);
    double time_elasped = 0.0;
    clock_t begin = clock();
    PrimeSieve *sieve = prime_init(SIZE);
    clock_t end = clock();
    printf("%d\n", prime_get_last(sieve));
    prime_iterator_reset(sieve);
    printf("%d\n", prime_get_next(sieve));
    prime_deinit(sieve);
    printf("Time spent = %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
    printf("Clocks spent = %f\n", (double) (end - begin));
    return 0;
}