//
// Created by bombehub on 2019/7/4.
//

#include <stdio.h>
#include "config.h"
#include <stdlib.h>


int main(){
    FILE *fid = fopen("key.txt", "r");
    FILE *fid2 = fopen("density.txt","r");
    FILE *out = fopen("data.txt","w");
    double *keys = (double *)malloc(sizeof(double)*DATASIZE);
    double *densitys = (double *)malloc(sizeof(double)*DATASIZE);
    double *cdfs = (double *)malloc(sizeof(double)*DATASIZE);
    if (fid == NULL || fid2 == NULL) {
        printf("open %s error\n");
        return 0;
    }
    char tmp1[32];
    for (int i = 0; i < DATASIZE; ++i) {
        fscanf(fid,"%s",tmp1);
        keys[i] = atof(tmp1);
    }

    for (int i = 0; i < DATASIZE; ++i) {
        fscanf(fid2,"%s",tmp1);
        densitys[i] = atof(tmp1);
    }
    cdfs[0]=densitys[0];
    for(int i=1;i<DATASIZE;i++){
        cdfs[i]=cdfs[i-1]+densitys[i];
    }

    double sum=0;
    for (int i = 0; i < DATASIZE; ++i) {
        sum+=densitys[i];
    }
    printf("%f",sum);
    for (int i = 0; i < DATASIZE; ++i) {
        fprintf(out, "%.12f,%.12f\n", keys[i], cdfs[i]);
        //printf("%f,%f\n",keys[i],cdfs[i]);
    }
    fclose(out);
    return 0;
}
