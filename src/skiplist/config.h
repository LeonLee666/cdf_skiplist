//
// Created by bombehub on 2/27/2019.
//

#ifndef SKIPLIST_CONFIG_H
#define SKIPLIST_CONFIG_H

#include <stddef.h>

#define MAXLEVEL 32
#define MAX_PARTITION_LEVEL 13
#define MAXPARTITION 8192

#define HOT_LEVEL 20

size_t get_size();
void set_size(size_t size);
#endif //SKIPLIST_CONFIG_H
