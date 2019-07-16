#!/usr/bin/env bash
export PATH="$PATH:`pwd`/../cmake-build-debug/src/"
for i in 1 3 5 7 9 
do
	cd normal-$i
	echo =======normal $i============
	../skiplist_test_21 ${alg}
	cd ..
done
