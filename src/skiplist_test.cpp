#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include "SkipList.h"
#include "dataset.h"

#include <sys/time.h>

#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 1

int clock_gettime(int clk_id, struct timespec* t) {
    struct timeval now;
    int rv = gettimeofday(&now, NULL);
    if (rv) return rv;
    t->tv_sec  = now.tv_sec;
    t->tv_nsec = now.tv_usec * 1000;
    return 0;
}

using namespace std;
using namespace cdf_list;

int main(int argc,char* argv[]) {
    Skip_list<int> sl;
    dataset *ds = new dataset;

    float key;
    size_t level;
    int method = atoi(argv[1]);
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
    } else if (method == 3) {
        while (ds->getNextByPartitionCDF(key, level)) {
            sl.insert(key, key, level);
        }
    }

    //clock_t t=clock();   // 计算cpu周期
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int c = 0; c < DATASIZE; c++) {
        bool vt = sl.search(ds->getKey(c));
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    double duration = ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000)/1000.0;
    std::cout << "Searching time=" << duration << "s.  QPS=" << (DATASIZE/duration)/10000<<" W/s\n";


    //sl.toString();
    delete ds;
    return 0;
}