/*
 * Copyright (C) 2015, Leo Ma <begeekmyfriend@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>

#if defined(__MACH__) && !defined(CLOCK_REALTIME)
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
#else

#include <time.h>

#endif

#include <stdio.h>
#include <memory.h>
#include "../common/skiplist.h"
#include "../common/config.h"
#include <math.h>

float *keys;
float *cdfs;

void loadData() {
    keys = (float*)malloc(sizeof(float)*DATASIZE);
    cdfs = (float*)malloc(sizeof(float)*DATASIZE);
    FILE *fid = fopen(dataset, "r");
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






int main()
{
    loadData();
    skip_list *sl=create_sl();
    int i=0;
    struct timespec start, end;



    printf("Test start!\n");
    printf("Add %d nodes...\n", DATASIZE);
    /* Insert test */
    srandom(time(NULL));
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(i=0;i<DATASIZE; ++i)
    {
        //printf("%f\n"),keys[i]);
        insert(sl, keys[i], keys[i],randomLevel());
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("time span: %ldms\n", (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000);
////////////////////////////////////
    printf("Now search each node...\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(i=0;i<DATASIZE; ++i)
    {
        search(sl, keys[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("time span: %ldms\n", (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000);
/////////////////////////////////////////



    printf("Now remove all nodes...\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (i = 0; i < DATASIZE; i++) {
        erase(sl, keys[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("time span: %ldms\n", (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000);

    //print_sl(sl);

    sl_free(sl);
    return 0;
}
