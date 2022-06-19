extern "C"
{
#include "memfunc.h"
#include <string.h>
#include <stdio.h>
}
#include <gtest/gtest.h>


class MemFuncTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
public: 
};

TEST_F(MemFuncTest, Transfer1Byte)
{
    char src = 0x55;
    char dest = 0;
    my_memcpy(&dest, &src, 1);
    ASSERT_EQ(src, dest);
}

TEST_F(MemFuncTest, Transfer4Byte)
{
    int src = 0x55555555;
    int dest = 0;
    my_memcpy(&dest, &src, sizeof(src));
    ASSERT_EQ(src, dest);
}

TEST_F(MemFuncTest, Transfer400Bytes)
{
    int src[100] = {0};
    int dest[100] = {0};
    for (int i = 0; i < 100; i++) {
        src[i] = 0x55;
    }
    my_memcpy((int *) dest, src, 100 * sizeof(int));
    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(src[i], dest[i]);
    }
}

TEST_F(MemFuncTest, TransferUnalignedBytes)
{
    char src[777] = {0};
    char dest[777] = {0};
    for (int i = 0; i < 777; i++) {
        src[i] = 0x55;
    }
    my_memcpy((int *) dest, src, 777 * sizeof(char));
    for (int i = 0; i < 777; i++) {
        ASSERT_EQ(src[i], dest[i]);
    }
}

TEST_F(MemFuncTest, Count0)
{
    char src = 1;
    char dest = 0;
    ASSERT_EQ(-1, my_memcpy(&dest, &src, 0));
}

TEST_F(MemFuncTest, Count1)
{
    char src = 42;
    char dest = 0;
    my_memcpy(&dest, &src, 1);
    ASSERT_EQ(dest, src);
}

TEST_F(MemFuncTest, Count2)
{
    char src[2] = {55, 21};
    char dest[2] = {0};
    my_memcpy(&dest, &src, 2);
    for (int i = 0; i < 2; i++) {
        ASSERT_EQ(dest[i], src[i]);
    }
}

TEST_F(MemFuncTest, Count3)
{
    char src[3] = {42, 43, 55};
    char dest[3] = {0};
    my_memcpy(dest, src, 3);
    for(int i = 0; i < 3; i++) {
        ASSERT_EQ(dest[i], src[i]);
    }
}

TEST_F(MemFuncTest, Count4)
{
    int src = 42121;
    int dest = 0;
    my_memcpy(&dest, &src, 4);
    ASSERT_EQ(dest, src);
}
