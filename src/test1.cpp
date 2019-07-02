#include <gtest/gtest.h>

#include <add.h>

TEST(group1,test1)
{
    ASSERT_TRUE(true);
    ASSERT_EQ(add(1,2),3);
}

TEST(group1,test2)
{
    ASSERT_EQ(add(1,2),4);
}
