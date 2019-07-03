#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include "SkipList.h"

using namespace std;
using namespace cdf_list;

int main() {
    constexpr int border = 8;
    Skip_list<int> sl;
    LinkList<int> sll;

    for (auto i = 0; i < border; ++i) {
        sl.insert(i, i);
        sll.push_back(i);
    }

    int val=3;

    clock_t t;

    t = clock();

    bool vt = sl.search(val);

    t = clock() - t;

    std::cout << "Search in the skip list took me " << t << " cycles (" << static_cast<float> (t) / CLOCKS_PER_SEC
              << " seconds).\n";

    t = clock();

    const ListNode<int> *p = sll.find(val);

    t = clock() - t;

    std::cout << "Search in the singly linked list took me " << t << " cycles ("
              << static_cast<float> (t) / CLOCKS_PER_SEC << " seconds).\n";

    if (vt) {
        std::cout << "Value " << p->val << " was found\n";
    }

    sl.toString();

    return 0;
}