#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include "skiplist/SkipList.h"
#include "skiplist/dataset.h"
#include "skiplist/config.h"
#include <sys/time.h>
#include "spdlog/spdlog.h"

#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 1

int clock_gettime(int clk_id, struct timespec *t) {
    struct timeval now;
    int rv = gettimeofday(&now, NULL);
    if (rv) return rv;
    t->tv_sec = now.tv_sec;
    t->tv_nsec = now.tv_usec * 1000;
    return 0;
}

using namespace std;
using namespace cdf_list;

void run_skiplist(int method, bool hot_test) {
    size_t datasize = get_size();
    Skip_list<float> sl;
    dataset *ds = new dataset;

    float key;
    size_t level;
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
    } else if (method == 4) {
        while (ds->getNextByHot(key, level)) {
            sl.insert(key, key, level);
        }
    } else if (method == 5) {
        while (ds->getNextByHotPlus(key, level)) {
            sl.insert(key, key, level);
        }
    }

    //clock_t t=clock();   // 计算cpu周期
    size_t count = 0;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (size_t itr = 0; itr < datasize; itr++) {
        bool vt = sl.search(ds->getKey(itr));
        count++;
    }
    if (hot_test) {
        // search hot keys for 100 times !!!
        for (int times = 1; times <= 80; times++) {
            for (size_t itr = 0; itr < 20971; itr++) {
                bool vt = sl.search(ds->getKey(itr));
                count++;
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    double duration = ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000) / 1000.0;
    spdlog::info("Skiplist = {}, QPS = {} W/s",method, (count / duration) / 10000);
    delete ds;
}


int main(int argc, char *argv[]) {
    if (argc != 8) {
        std::cout << "error\n";
        std::cout << "skiplist (maxlevel) (datasize) (hot-level) (partition-level) (partition) [0/1] [alglrithms]\n";
    }
    set_MAXLEVEL(atol(argv[1]));  //32
    set_size(atol(argv[2]));  //2097152,set_size(334863);
    set_HOT_LEVEL(atol(argv[3]));    // 20
    set_MAX_PARTITION_LEVEL(atol(argv[4]));  //    13
    set_MAXPARTITION(atol(argv[5]));  // 2^13

    if (atoi(argv[6]) == 0) {
        run_skiplist(atoi(argv[7]), false);
    } else {
        run_skiplist(atoi(argv[7]), true);
    }
    return 0;
}