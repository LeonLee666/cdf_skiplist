#!/usr/bin/env bash
for size in 1 3 5 7 
do
cd zipf-${size}
echo ===========zipf-${size}======================
for alg in 0 1 2 3
do
skiplist 32 2097152 20 13 8192 0 ${alg}
done
cd ..
done
