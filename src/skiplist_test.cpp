#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include "skiplist/SkipList.h"
#include "dataset.h"

using namespace std;
using namespace cdf_list;

int main() {
    Skip_list<int> sl;
    dataset ds;

    float key;
    size_t level;
    //while (ds.getNextByRandom(key, level)) {
    while (ds.getNextByPreciseCDF(key, level)) {
        //std::cout<<key<<","<<level<<"\n";
        sl.insert(key, key, level);
    }

    clock_t t;

    t = clock();
    for (int c = 0; c < DATASIZE; c++) {
        bool vt = sl.search(ds.getKey(c));
    }
    t = clock() - t;

    std::cout << "Search in the skip list took me " << t << " cycles (" << static_cast<float> (t) / CLOCKS_PER_SEC
              << " seconds).\n";

    //sl.toString();

    return 0;
}