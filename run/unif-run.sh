#!/usr/bin/env bash

declare -A map=(["15"]="32768" ["18"]="262144" ["21"]="2097152" ["24"]="16777216")
for size in ${!map[@]}
do
cd unif-${size}
echo ============unif-${size}==========================
for alg in 0 1 2 3
do
skiplist 32 ${map[$size]} 20 13 8192 0 ${alg}
done
cd ..
done
