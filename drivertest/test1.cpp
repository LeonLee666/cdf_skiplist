#include <gtest/gtest.h>



TEST(group1,test1)
{
    ASSERT_TRUE(true);
    ASSERT_EQ(1+2,3);
}

TEST(group1,test2)
{
    ASSERT_EQ(1+2,4);
}
