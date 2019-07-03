#include <gtest/gtest.h>
#include "List.h"

TEST(Link_test, Test_Constructor) {
    constexpr int var = 10;
    List_h::Link<int> l{var};
    ASSERT_TRUE(&l != NULL);
    ASSERT_EQ(var, l.val);
}

TEST(Link_test, Test_Insert) {
    constexpr int var_1 = 10;
    constexpr int var_2 = 20;
    List_h::Link<int> l_1{var_1};
    l_1.insert(new List_h::Link<int>{var_2});
    ASSERT_TRUE(l_1.next != NULL);
    ASSERT_EQ(var_2, l_1.next->val);
}

TEST(Link_test, Test_Copy) {
    constexpr int var = 50;
    List_h::Link<int> *l_1 = new List_h::Link<int>{var};
    List_h::Link<int> l_2 = *l_1;
    delete l_1;
    l_1 = nullptr;
    ASSERT_EQ(var, l_2.val);
}
