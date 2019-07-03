#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include "SkipList.h"
#include "dataset.h"

using namespace std;
using namespace cdf_list;

int main() {
    Skip_list<int> sl;
    dataset *ds = new dataset;

    float key;
    size_t level;
    int method = 0;
    if (method == 0) {
        while (ds->getNextByRandom(key, level)) {
            sl.insert(key, key, level);
        }
    } else if (method == 1) {
        while (ds->getNextByPreciseCDF(key, level)) {
            sl.insert(key, key, level);
        }
    } else if (method == 2) {
        while (ds->getNextByEstimateCDF(key, level)) {
            sl.insert(key, key, level);
        }
    }

    clock_t t;

    t = clock();
    for (int c = 0; c < DATASIZE; c++) {
        bool vt = sl.search(ds->getKey(c));
    }
    t = clock() - t;

    std::cout << "Search in the skip list took me " << t << " cycles (" << static_cast<float> (t) / CLOCKS_PER_SEC
              << " seconds).\n";

    //sl.toString();
    delete ds;
    return 0;
}