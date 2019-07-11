#!/usr/bin/env bash
for i in {1..10}
do
	cd normal-$i
	echo generating dataset $i
	Rscript normal.r
	cd ..
done
