extern "C"
{
#include "linked_list.h"
#include <string.h>
#include <stdio.h>
}
#include <gtest/gtest.h>


class LLTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        list = ll_new();
    }

    void TearDown() override
    {
        ll_destroy(list);
    }
public: 
    struct LinkedList *list = NULL;
};

TEST_F(LLTest, EmptyList)
{
    ASSERT_EQ(ll_get(list, 0), (void *) NULL);
    ASSERT_EQ(ll_get(list, 5), (void *) NULL);
}

TEST_F(LLTest, SingleAdd)
{
    int val = 5;
    ll_add(list, (void *) &val);
    int *val_ptr = (int *) ll_get(list, 0);
    ASSERT_EQ(*val_ptr, val);
}

TEST_F(LLTest, DoubleAdd)
{
    int val = 5;
    ll_add(list, (void *) &val);
    ll_add(list, (void *) &val);
    int *val_ptr = (int *) ll_get(list, 0);
    ASSERT_EQ(*val_ptr, val);
    val_ptr = (int *) ll_get(list, 1);
    ASSERT_EQ(*val_ptr, val);
}


TEST_F(LLTest, MultipleAdd)
{
    int data[10] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++) {
        ll_add(list, (void *) &data[i]);
    }
    for (int i = 0; i < 10; i++) {
        int *tmp = (int *) ll_get(list, i);
        ASSERT_EQ(*tmp, data[i]);
    }
}

TEST_F(LLTest, MultipleAddSingleRemove)
{
    int data[10] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int data_next[9] = {1, 2, 3, 4, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++) {
        ll_add(list, (void *) &data[i]);
    }
    ll_remove(list, &data[4]);
    for (int i = 0; i < 9; i++) {
        int *tmp = (int *) ll_get(list, i);
        ASSERT_EQ(data_next[i], *tmp);
    }
}

TEST_F(LLTest, MultipleAddDoubleRemove)
{
    int data[10] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int data_next[9] = {1, 2, 3, 4, 6, 7, 8, 10};
    for (int i = 0; i < 10; i++) {
        ll_add(list, (void *) &data[i]);
    }
    ll_remove(list, &data[4]);
    ll_remove(list, &data[8]);
    for (int i = 0; i < 8; i++) {
        int *tmp = (int *) ll_get(list, i);
        ASSERT_EQ(data_next[i], *tmp);
    }
}

TEST_F(LLTest, EmptyRemove)
{
    int data = 4;
    ASSERT_EQ(ll_remove(list, &data), -1);
}

TEST_F(LLTest, EmptyLast)
{
    int data[10] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int data_next[7] = {1, 2, 3, 4, 6, 7, 8};
    for (int i = 0; i < 10; i++) {
        ll_add(list, (void *) &data[i]);
    }
    ll_remove(list, &data[4]);
    ll_remove(list, &data[8]);
    ll_remove(list, &data[9]);
    for (int i = 0; i < 7; i++) {
        int *tmp = (int *) ll_get(list, i);
        ASSERT_EQ(data_next[i], *tmp);
    }
}

TEST_F(LLTest, GetBeyond)
{
    int data[10] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++) {
        ll_add(list, (void *) &data[i]);
    }
    int *tmp = (int *) ll_get(list, 15);
    ASSERT_EQ(tmp, (int *) NULL);
}

TEST_F(LLTest, GetBeyondAfterRemoveLast)
{
    int data[10] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int data_next[7] = {1, 2, 3, 4, 6, 7, 8};
    for (int i = 0; i < 10; i++) {
        ll_add(list, (void *) &data[i]);
    }
    ll_remove(list, &data[4]);
    ll_remove(list, &data[8]);
    ll_remove(list, &data[9]);
    int *tmp = (int *) ll_get(list, 14);
    ASSERT_EQ(tmp, (int *) NULL);
}
