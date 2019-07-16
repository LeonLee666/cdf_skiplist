//
// Created by bombehub on 2/27/2019.
//

#ifndef SKIPLIST_CONFIG_H
#define SKIPLIST_CONFIG_H

#include <stddef.h>

size_t get_MAXLEVEL();
void set_MAXLEVEL(size_t size);

size_t get_MAX_PARTITION_LEVEL();
void set_MAX_PARTITION_LEVEL(size_t size);

size_t get_MAXPARTITION();
void set_MAXPARTITION(size_t size);

size_t get_HOT_LEVEL();
void set_HOT_LEVEL(size_t size);

size_t get_size();
void set_size(size_t size);

#endif //SKIPLIST_CONFIG_H
