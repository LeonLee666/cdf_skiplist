#include <gtest/gtest.h>
#include "SkipList.h"

TEST(Link_test, Test_Constructor) {
    constexpr int var = 10;
    cdf_list::Skip_node<float> l(var, var, 2);
    ASSERT_TRUE(&l != NULL);
    ASSERT_EQ(var, l.val);
}

TEST(Link_test, Test_Equal) {
    constexpr int var_1 = 10;
    constexpr int var_2 = 20;
    cdf_list::Skip_node<float> l_1(var_1, var_1, 2);
    cdf_list::Skip_node<float> l_2(var_2, var_2, 2);
    ASSERT_TRUE(l_1.key != l_2.key);
    ASSERT_TRUE(l_1.val != l_2.val);
}


