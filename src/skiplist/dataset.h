//
// Created by bombehub on 2/27/2019.
//

#pragma once

#include "skiplist/config.h"
#include <cmath>
#include <cstdlib>
#include <cstdio>

class dataset {
public:
    size_t max_lvl = get_MAXLEVEL();
    size_t max_parlevel = get_MAX_PARTITION_LEVEL();
    size_t max_partition = get_MAXPARTITION();
    size_t hot_level = get_HOT_LEVEL();
    size_t max_hot_partition = hot_level>max_parlevel?hot_level:max_parlevel;
    float getKey(size_t offset) {
        return keys[offset];
    }

    bool getNextByRandom(float &key, size_t &level) {
        if (itr < size) {
            key = keys[itr];
            level = random_level(max_lvl);
            itr++;
            return true;
        } else {
            return false;
        }
    }

    bool getNextByPreciseCDF(float &key, size_t &level) {
        if (itr < size) {
            key = keys[itr];
            size_t location = (size_t) (cdfs[itr] * size);
            size_t lv = 1;
            size_t step = 2;
            while (step <= location) {
                if (location % step == 0) {
                    lv++;
                }
                step = step << 1;
            }
            level = lv;
            itr++;
            return true;
        } else {
            return false;
        }
    }

    bool getNextByEstimateCDF(float &key, size_t &level) {
        if (itr < size) {
            key = keys[itr];
            size_t location = (size_t) (cdfs[itr] * size);
            int bound = 1;
            size_t lower_bound = (location - bound > 1) ? (location - bound) : 1;
            size_t upper_bound = (location + bound < size) ? (location + bound) : size;
            int lv = 0;
            for (size_t i = lower_bound; i <= upper_bound; i++) {
                if (level_array[i] >= lv) {
                    lv = level_array[i];
                    level_array[i] = 1;
                }
            }
            level = lv;
            itr++;
            return true;
        } else {
            return false;
        }
    }

    bool getNextByPartitionCDF(float &key, size_t &level) {
        if (itr < size) {
            key = keys[itr];
            int lv = 0;
            size_t partition = (size_t) (cdfs[itr] * (max_partition)-1);
            if (partition_array[partition] != 0) {
                lv = partition_array[partition];
                partition_array[partition] = 0;
            } else {
                lv = random_level(max_lvl - max_parlevel);
            }
            level = lv;
            itr++;
            return true;
        } else {
            return false;
        }
    }

    bool getNextByHot(float &key, size_t &level) {
        if (itr < size) {
            key = keys[itr];
            if (itr < 20971) {  // hot key
                level = random_level(hot_level) + max_lvl - hot_level;
                //partition_array[partition]=0;
            } else {
                level = random_level(max_lvl - hot_level);
            }
            itr++;
            return true;
        } else {
            return false;
        }
    }

    bool getNextByHotPlus(float &key, size_t &level) {
        if (itr < size) {
            key = keys[itr];
            size_t partition = (size_t) (cdfs[itr] * (max_partition)-1);
            if (itr < 20971) {  // hot key
                level = random_level(hot_level) + max_lvl - hot_level;
                partition_array[partition]=0;
            } else {
                int lv;
                if (partition_array[partition] != 0) {
                    lv = partition_array[partition];
                    partition_array[partition] = 0;
                } else {
                    lv = random_level(max_lvl - max_hot_partition);
                }
                level = lv;
            }
            itr++;
            return true;
        } else {
            return false;
        }
    }


    dataset() {
        size = get_size();
        itr = 0;
        keys = (float *) malloc(sizeof(float) * size);
        cdfs = (float *) malloc(sizeof(float) * size);
        level_array = (int *) malloc(sizeof(int) * (size + 1));
        partition_array = (int *) malloc(sizeof(int) * max_partition);
        loadData();
        buildArray();
        srand(time(NULL));
    }

    ~dataset() {
        free(keys);
        free(cdfs);
        free(level_array);
        free(partition_array);
    }

private:
    // Generating random level for Skip Nodes
    size_t random_level(size_t maxlevel) {
        int level = 1;
        while (level < maxlevel && rand() % 10 < 5) {
            level++;
        }
        return level;
    }

    void loadData() {
        FILE *fid = fopen("dataset.dat", "r");
        if (fid == NULL) {
            printf("open %s error", "dataset.dat");
            return;
        }
        char tmp1[32];
        char tmp2[32];
        for (int i = 0; i < size; ++i) {
            fscanf(fid, "%[^,],%s", tmp1, tmp2);
            keys[i] = atof(tmp1);
            cdfs[i] = atof(tmp2);
            //printf("%f,%f\n",keys[i],cdfs[i]);
        }
    }

    void buildArray() {
        for (size_t i = 0; i <= size; i++) {
            level_array[i] = 0;
        }
        size_t step = 1;
        while (step < size) {
            for (size_t i = 0; i <= size; i += step) {
                ++(level_array[i]);
            }
            step = step << 1;
        }
////////////////////////////////////////////////////
        for (size_t i = 0; i < max_partition; i++) {
            partition_array[i] = max_lvl - max_parlevel;
        }
        step = 1;
        while (step < max_partition) {
            for (size_t i = 0; i < max_partition; i += step) {
                ++(partition_array[i]);
            }
            step = step << 1;
        }
    }

private:
    float *keys;
    float *cdfs;
    size_t size;
    int itr;
    int *level_array;
    int *partition_array;
};