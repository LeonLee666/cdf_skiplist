#!/usr/bin/env bash
export PATH="$PATH:`pwd`/../cmake-build-debug/src/"
for size in 1 3 5 7 
do
cd zipf-${size}
echo ===========zipf-${size}======================
../skiplist_test_21 
cd ..
done
