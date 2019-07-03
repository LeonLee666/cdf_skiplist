//
// Created by bombehub on 2/27/2019.
//

#pragma once

#include "config.h"
#include <math.h>
#include <stdlib.h>


class args{
private:
    int K;
    int MAXLEVEL;
    int *arr;
public:
    args(int k, int maxlevel){
        this->K = k;
        this->MAXLEVEL = maxlevel;
        this->arr = (int *) malloc(sizeof(int) * DATASIZE);
        for (int i = 0; i < DATASIZE; i++) {
            this->arr[i] = 0;
        }
        int _level = 0;
        while (_level < k) {
            int step = (int) pow(2, _level);
            for (int i = 0; i < DATASIZE; i += step) {
                ++(this->arr[i]);
            }
            _level++;
        }
    }
    ~args(){
        free(arr);
    }
    int ai_random(float cdf) {
        int result = arr[(int)(cdf * DATASIZE) - 1];
        arr[(int)(cdf * DATASIZE) - 1] = 1;
        return  result;
    }
};


