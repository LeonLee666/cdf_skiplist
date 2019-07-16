#!/usr/bin/env bash
for i in 15 18 21 24
do
	cd unif-$i
	echo generating dataset $i
	Rscript unif.r
	cd ..
done
