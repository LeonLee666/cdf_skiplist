#include <gtest/gtest.h>
#include "SkipList.h"

TEST(Slink_Test, Test_Default_Constructor) {
    cdf_list::LinkList<int> sl;

    ASSERT_TRUE(sl.get_head() == NULL);
}

TEST(Slink_Test, Test_Init_Constructor) {
    constexpr size_t sz = 5;
    cdf_list::LinkList<int> sl{1, 2, 3, 4, 5};

    ASSERT_EQ(sz, sl.size());
}

TEST(Slink_Test, Test_Find_Exist) {
    const std::string search_w1{"Line"};
    const std::string search_w2{"ln"};
    cdf_list::LinkList<std::string> sl{"hello", "world", "line", "Line", "ln"};

    const cdf_list::ListNode<std::string> *p1 = sl.find(search_w1);
    const cdf_list::ListNode<std::string> *p2 = sl.find(search_w2);

    ASSERT_EQ(p1->val, search_w1);
    ASSERT_EQ(p2->val, search_w2);
}

TEST(Slink_Test, Test_Find_Null) {
    constexpr int val = 10;
    cdf_list::LinkList<int> sl{1, 2, 3};

    const cdf_list::ListNode<int> *p1 = sl.find(val);

    ASSERT_TRUE(p1 == NULL);
}
