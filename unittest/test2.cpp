#include <gtest/gtest.h>
#include "SkipList.h"

TEST(Slink_Test, Test_Find_Exist) {
    const std::string search_w1{"Line"};
    const std::string search_w2{"ln"};
    cdf_list::Skip_list<std::string> sl;

    sl.insert(1, search_w1, 3);
    sl.insert(2, search_w2, 2);

    ASSERT_TRUE(sl.search(1));
    ASSERT_TRUE(sl.search(2));
}
