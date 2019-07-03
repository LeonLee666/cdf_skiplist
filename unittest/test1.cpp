#include <gtest/gtest.h>
#include "SkipList.h"

TEST(Link_test, Test_Constructor) {
    constexpr int var = 10;
    cdf_list::ListNode<int> l{var};
    ASSERT_TRUE(&l != NULL);
    ASSERT_EQ(var, l.val);
}

TEST(Link_test, Test_Insert) {
    constexpr int var_1 = 10;
    constexpr int var_2 = 20;
    cdf_list::ListNode<int> l_1{var_1};
    l_1.insert(new cdf_list::ListNode<int>{var_2});
    ASSERT_TRUE(l_1.next != NULL);
    ASSERT_EQ(var_2, l_1.next->val);
}

TEST(Link_test, Test_Copy) {
    constexpr int var = 50;
    cdf_list::ListNode<int> *l_1 = new cdf_list::ListNode<int>{var};
    cdf_list::ListNode<int> l_2 = *l_1;
    delete l_1;
    l_1 = nullptr;
    ASSERT_EQ(var, l_2.val);
}


