extern "C"
{
#include "prime.h"
#include <string.h>
#include <stdio.h>
}
#include <gtest/gtest.h>


class PrimeTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        test_prime_sieve_ = prime_init(100);
    }

    void TearDown() override
    {
        prime_deinit(test_prime_sieve_);
    }
public: 
    PrimeSieve *test_prime_sieve_ = NULL;
};

TEST_F(PrimeTest, FirstPrime)
{
    ASSERT_EQ(2, prime_get_next(test_prime_sieve_));
}

TEST_F(PrimeTest, FirstPrimes)
{
    ASSERT_EQ(2, prime_get_next(test_prime_sieve_));
    ASSERT_EQ(3, prime_get_next(test_prime_sieve_));
    ASSERT_EQ(5, prime_get_next(test_prime_sieve_));
    ASSERT_EQ(7, prime_get_next(test_prime_sieve_));
}

TEST_F(PrimeTest, LastPrime)
{
    ASSERT_EQ(97, prime_get_last(test_prime_sieve_));
}

TEST_F(PrimeTest, FirstPrimesAndReset)
{
    ASSERT_EQ(2, prime_get_next(test_prime_sieve_));
    ASSERT_EQ(3, prime_get_next(test_prime_sieve_));
    ASSERT_EQ(5, prime_get_next(test_prime_sieve_));
    ASSERT_EQ(7, prime_get_next(test_prime_sieve_));
    prime_iterator_reset(test_prime_sieve_);
    ASSERT_EQ(2, prime_get_next(test_prime_sieve_));
}

TEST_F(PrimeTest, RigorousPrimes100)
{
    int rigorousprimes100[25] = {
        2, 3, 5, 7,
        11, 13, 17, 19,
        23, 29,
        31, 37,
        41, 43, 47,
        53, 59, 
        61, 67, 
        71, 73, 79,
        83, 89,
        97
    };
    int i;
    for (i = 0; i < 25; i++)
    {
        ASSERT_EQ(rigorousprimes100[i], prime_get_next(test_prime_sieve_));
    }
}
