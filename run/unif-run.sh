#!/usr/bin/env bash
export PATH="$PATH:`pwd`/../cmake-build-debug/src/"
for size in 15 18 21 24
do
cd unif-${size}
echo ============unif-${size}==========================
../skiplist_test_${size} 
cd ..
done
