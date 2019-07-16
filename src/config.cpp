//
// Created by db on 19-7-9.
//

#include "skiplist/config.h"

size_t sz;
size_t max_level;
size_t partition;
size_t partition_level;
size_t hot_level;

void set_size(size_t size){
    sz=size;
}
size_t get_size() {
    return sz;
}

size_t get_MAXLEVEL(){
    return max_level;
}
void set_MAXLEVEL(size_t size){
    max_level = size;
}

size_t get_MAX_PARTITION_LEVEL(){
    return partition_level;
}
void set_MAX_PARTITION_LEVEL(size_t size){
    partition_level=size;
}

size_t get_MAXPARTITION(){
    return partition;
}
void set_MAXPARTITION(size_t size){
    partition=size;
}

size_t get_HOT_LEVEL(){
    return hot_level;
}
void set_HOT_LEVEL(size_t size){
    hot_level=size;
}

