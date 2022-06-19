extern "C"
{
#include "c_string.h"
#include <string.h>
#include <stdio.h>

const char* test_str = "Test";
}
#include <gtest/gtest.h>


class CStringTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        test_string_ = string_new(test_str);
    }

    void TearDown() override
    {
        string_delete(test_string_);
    }
public: 
    CString test_string_ = NULL;
};

TEST_F(CStringTest, NewDel)
{
    ASSERT_EQ(0, strcmp(test_str, test_string_));
    ASSERT_EQ(strlen(test_str), strlen(test_string_));
}

TEST_F(CStringTest, Insert0)
{
    string_insert(test_string_, 0, 'K');
    ASSERT_EQ(0, strcmp("KTest", test_string_));
    ASSERT_EQ(strlen(test_str) + 1, strlen(test_string_));
}

TEST_F(CStringTest, Insert1)
{
    string_insert(test_string_, 1, 'K');
    ASSERT_EQ(0, strcmp("TKest", test_string_));
    ASSERT_EQ(strlen(test_str) + 1, strlen(test_string_));
}

TEST_F(CStringTest, Insert2)
{
    string_insert(test_string_, 2, 'K');
    ASSERT_EQ(0, strcmp("TeKst", test_string_));
    ASSERT_EQ(strlen(test_str) + 1, strlen(test_string_));
}

TEST_F(CStringTest, Insert3)
{
    string_insert(test_string_, 3, 'K');
    ASSERT_EQ(0, strcmp("TesKt", test_string_));
    ASSERT_EQ(strlen(test_str) + 1, strlen(test_string_));
}

TEST_F(CStringTest, Insert4)
{
    string_insert(test_string_, 4, 'K');
    ASSERT_EQ(0, strcmp("TestK", test_string_));
    ASSERT_EQ(strlen(test_str) + 1, strlen(test_string_));
}

TEST_F(CStringTest, InsertOutOfBound)
{
    ASSERT_EQ(-1, string_insert(test_string_, 5, 'K'));
    ASSERT_EQ(0, strcmp("Test", test_string_));
    ASSERT_EQ(strlen(test_str), strlen(test_string_));
}

TEST_F(CStringTest, InsertStr)
{
    string_insert_str(test_string_, 0, (char*) "Me");
    ASSERT_EQ(0, strcmp("MeTest", test_string_));
    ASSERT_EQ(strlen(test_str) + 2, strlen(test_string_));
}

TEST_F(CStringTest, InsertStrEnd)
{
    ASSERT_EQ(0, string_insert_str(test_string_, 4, (char*) "Me"));
    ASSERT_EQ(0, strcmp("TestMe", test_string_));
    ASSERT_EQ(strlen(test_str) + 2, strlen(test_string_));
}
