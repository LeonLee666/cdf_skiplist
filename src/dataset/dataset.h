//
// Created by bombehub on 2/27/2019.
//

#pragma once

#include "config.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

class dataset {
public:
    static constexpr size_t max_lvl = MAXLEVEL;

    float getKey(size_t offset) {
        return keys[offset];
    }

    bool getNextByRandom(float &key, size_t &level) {
        if (itr < size) {
            key = keys[itr];
            level = random_level();
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
    dataset() {
        size = DATASIZE;
        itr = 0;
        keys = (float *) malloc(sizeof(float) * size);
        cdfs = (float *) malloc(sizeof(float) * size);
        level_array = (int *) malloc(sizeof(int) * (size + 1));
        loadData();
        buildArray();
        srand(12345);
    }
private:
    // Generating random level for Skip Nodes
    size_t random_level() {
        int level = 1;
        while (level < max_lvl && rand() % 10 < 5) {
            level++;
        }
        return level;
    }
    void loadData() {
        FILE *fid = fopen("../../dataset.txt", "r");
        if (fid == NULL) {
            printf("open %s error", "dataset.txt");
            return;
        }
        char tmp1[32];
        char tmp2[32];
        for (int i = 0; i < DATASIZE; ++i) {
            fscanf(fid, "%[^,],%s", tmp1, tmp2);
            keys[i] = atof(tmp1);
            cdfs[i] = atof(tmp2);
            //printf("%f,%f\n",keys[i],cdfs[i]);
        }
    }
    void buildArray() {

    }
private:
    float *keys;
    float *cdfs;
    size_t size;
    int itr;
    int *level_array;
};