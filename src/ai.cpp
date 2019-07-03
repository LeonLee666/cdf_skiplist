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
#include "skiplist.h"
#include "config.h"
#include <math.h>
#include "skiplist_ai.h"
// #define SKIPLIST_DEBUG


args AI();
float keys[DATASIZE];
float cdfs[DATASIZE];


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

int main(void) {
    loadData();
    ai_init(&AI, (int) ceil(log(DATASIZE) / log(2)), MLEVEL);
    float *key = malloc(DATASIZE * sizeof(float));
    int i;
    struct timespec start, end;
    if (key == NULL) {
        exit(-1);
    }
    struct skiplist *list = skiplist_new();
    if (list == NULL) {
        exit(-1);
    }
    printf("Test start!\n");
    printf("Add %d nodes...\n", DATASIZE);

    /* Insert test */
    srandom(time(NULL));
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (i = 0; i < DATASIZE; i++) {
        key[i] = keys[i];1
        skiplist_insert(list, keys[i], keys[i], ai_random(&AI, cdfs[i]));
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("time span: %ldms\n", (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000);
#ifdef SKIPLIST_DEBUG
    skiplist_dump(list);
#endif

    /* Search test */
    printf("Now search each node...\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (i = 0; i < DATASIZE; i++) {
        //printf("%f,",key[i]);
        struct skipnode *node = skiplist_search(list, keys[i]);
        if (node != NULL) {

            //printf("key:%f value:%f\n", node->key, node->value);

        } else {
            printf("Not found:%f\n", key[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("time span: %ldms\n", (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000);

    /* Delete test */
    printf("Now remove all nodes...\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (i = 0; i < DATASIZE; i++) {
        skiplist_remove(list, key[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("time span: %ldms\n", (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000);
#ifdef SKIPLIST_DEBUG
    skiplist_dump(list);
#endif

    printf("End of Test.\n");
    skiplist_delete(list);

    free(key);

    return 0;
}
